/*
 * Copyright (c) 2020 Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ti_bq274xx

#include <zephyr/drivers/i2c.h>
#include <zephyr/init.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/pm/device.h>
#include <zephyr/sys/__assert.h>
#include <string.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "bq274xx.h"

LOG_MODULE_REGISTER(bq274xx, CONFIG_SENSOR_LOG_LEVEL);

/* subclass 64 & 82 needs 5ms delay */
#define BQ274XX_SUBCLASS_DELAY 5

/* Time to set pin in order to exit shutdown mode */
#define PIN_DELAY_TIME         1U

/* Time it takes device to initialize before doing any configuration */
#define INIT_TIME              100U

static int gauge_configure(const struct device *dev);

static int cmd_reg_read(const struct device *dev, uint8_t reg_addr, int16_t *val)
{
	const struct bq274xx_config *config = dev->config;
	uint8_t i2c_data[2];
	int ret;

	ret = i2c_burst_read_dt(&config->i2c, reg_addr, i2c_data, 2);
	if (ret < 0) {
		LOG_ERR("Unable to read register");
		return -EIO;
	}

	*val = (i2c_data[1] << 8) | i2c_data[0];

	return 0;
}

static int ctrl_reg_write(const struct device *dev, uint16_t subcommand)
{
	const struct bq274xx_config *config = dev->config;
	uint8_t i2c_data, reg_addr;
	int ret = 0;

	reg_addr = BQ274XX_CMD_CONTROL_LOW;
	i2c_data = (uint8_t)((subcommand)&0x00FF);

	ret = i2c_reg_write_byte_dt(&config->i2c, reg_addr, i2c_data);
	if (ret < 0) {
		LOG_ERR("Failed to write into control low register");
		return -EIO;
	}

	k_msleep(BQ274XX_SUBCLASS_DELAY);

	reg_addr = BQ274XX_CMD_CONTROL_HIGH;
	i2c_data = (uint8_t)((subcommand >> 8) & 0x00FF);

	ret = i2c_reg_write_byte_dt(&config->i2c, reg_addr, i2c_data);
	if (ret < 0) {
		LOG_ERR("Failed to write into control high register");
		return -EIO;
	}

	return 0;
}

static int cmd_reg_write(const struct device *dev, uint8_t command, uint8_t data)
{
	const struct bq274xx_config *config = dev->config;
	uint8_t i2c_data, reg_addr;
	int ret = 0;

	reg_addr = command;
	i2c_data = data;

	ret = i2c_reg_write_byte_dt(&config->i2c, reg_addr, i2c_data);
	if (ret < 0) {
		LOG_ERR("Failed to write into control register");
		return -EIO;
	}

	return 0;
}

static int read_data_block(const struct device *dev, uint8_t offset,
			   uint8_t *data, uint8_t bytes)
{
	const struct bq274xx_config *config = dev->config;
	uint8_t i2c_data;
	int ret = 0;

	i2c_data = BQ274XX_EXT_BLKDAT_START + offset;

	ret = i2c_burst_read_dt(&config->i2c, i2c_data, data, bytes);
	if (ret < 0) {
		LOG_ERR("Failed to read block");
		return -EIO;
	}

	k_msleep(BQ274XX_SUBCLASS_DELAY);

	return 0;
}

static int get_device_type(const struct device *dev, uint16_t *val)
{
	int ret;

	ret = ctrl_reg_write(dev, BQ274XX_CTRL_DEVICE_TYPE);
	if (ret < 0) {
		LOG_ERR("Unable to write control register");
		return -EIO;
	}

	ret = cmd_reg_read(dev, BQ274XX_CMD_CONTROL_LOW, val);

	if (ret < 0) {
		LOG_ERR("Unable to read register");
		return -EIO;
	}

	return 0;
}

/**
 * @brief sensor value get
 *
 * @return -ENOTSUP for unsupported channels
 */
static int channel_get(const struct device *dev, enum sensor_channel chan,
		       struct sensor_value *val)
{
	struct bq274xx_data *data = dev->data;
	float int_temp;

	switch (chan) {
	case SENSOR_CHAN_GAUGE_VOLTAGE:
		val->val1 = ((data->voltage / 1000));
		val->val2 = ((data->voltage % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_AVG_CURRENT:
		val->val1 = ((data->avg_current / 1000));
		val->val2 = ((data->avg_current % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_STDBY_CURRENT:
		val->val1 = ((data->stdby_current / 1000));
		val->val2 = ((data->stdby_current % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_MAX_LOAD_CURRENT:
		val->val1 = ((data->max_load_current / 1000));
		val->val2 = ((data->max_load_current % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_TEMP:
		int_temp = (data->internal_temperature * 0.1f);
		int_temp = int_temp - 273.15f;
		val->val1 = (int32_t)int_temp;
		val->val2 = (int_temp - (int32_t)int_temp) * 1000000;
		break;

	case SENSOR_CHAN_GAUGE_STATE_OF_CHARGE:
		val->val1 = data->state_of_charge;
		val->val2 = 0;
		break;

	case SENSOR_CHAN_GAUGE_STATE_OF_HEALTH:
		val->val1 = data->state_of_health;
		val->val2 = 0;
		break;

	case SENSOR_CHAN_GAUGE_FULL_CHARGE_CAPACITY:
		val->val1 = (data->full_charge_capacity / 1000);
		val->val2 = ((data->full_charge_capacity % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_REMAINING_CHARGE_CAPACITY:
		val->val1 = (data->remaining_charge_capacity / 1000);
		val->val2 = ((data->remaining_charge_capacity % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_NOM_AVAIL_CAPACITY:
		val->val1 = (data->nom_avail_capacity / 1000);
		val->val2 = ((data->nom_avail_capacity % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_FULL_AVAIL_CAPACITY:
		val->val1 = (data->full_avail_capacity / 1000);
		val->val2 = ((data->full_avail_capacity % 1000) * 1000U);
		break;

	case SENSOR_CHAN_GAUGE_AVG_POWER:
		val->val1 = (data->avg_power / 1000);
		val->val2 = ((data->avg_power % 1000) * 1000U);
		break;

	default:
		return -ENOTSUP;
	}

	return 0;
}

static int sample_fetch(const struct device *dev, enum sensor_channel chan)
{
	struct bq274xx_data *data = dev->data;
	int ret = 0;

	if (!data->configured) {
		ret = gauge_configure(dev);

		if (ret < 0) {
			return ret;
		}
	}

	switch (chan) {
	case SENSOR_CHAN_GAUGE_VOLTAGE:
		ret = cmd_reg_read(dev, BQ274XX_CMD_VOLTAGE, &data->voltage);
		if (ret < 0) {
			LOG_ERR("Failed to read voltage");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_AVG_CURRENT:
		ret = cmd_reg_read(dev, BQ274XX_CMD_AVG_CURRENT,
				   &data->avg_current);
		if (ret < 0) {
			LOG_ERR("Failed to read average current ");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_TEMP:
		ret = cmd_reg_read(dev, BQ274XX_CMD_INT_TEMP,
				   &data->internal_temperature);
		if (ret < 0) {
			LOG_ERR("Failed to read internal temperature");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_STDBY_CURRENT:
		ret = cmd_reg_read(dev, BQ274XX_CMD_STDBY_CURRENT,
				   &data->stdby_current);
		if (ret < 0) {
			LOG_ERR("Failed to read standby current");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_MAX_LOAD_CURRENT:
		ret = cmd_reg_read(dev, BQ274XX_CMD_MAX_CURRENT,
				   &data->max_load_current);
		if (ret < 0) {
			LOG_ERR("Failed to read maximum current");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_STATE_OF_CHARGE:
		ret = cmd_reg_read(dev, BQ274XX_CMD_SOC, &data->state_of_charge);
		if (ret < 0) {
			LOG_ERR("Failed to read state of charge");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_FULL_CHARGE_CAPACITY:
		ret = cmd_reg_read(dev, BQ274XX_CMD_FULL_CAPACITY,
				   &data->full_charge_capacity);
		if (ret < 0) {
			LOG_ERR("Failed to read full charge capacity");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_REMAINING_CHARGE_CAPACITY:
		ret = cmd_reg_read(dev, BQ274XX_CMD_REM_CAPACITY,
				   &data->remaining_charge_capacity);
		if (ret < 0) {
			LOG_ERR("Failed to read remaining charge capacity");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_NOM_AVAIL_CAPACITY:
		ret = cmd_reg_read(dev, BQ274XX_CMD_NOM_CAPACITY,
				   &data->nom_avail_capacity);
		if (ret < 0) {
			LOG_ERR("Failed to read nominal available capacity");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_FULL_AVAIL_CAPACITY:
		ret = cmd_reg_read(dev, BQ274XX_CMD_AVAIL_CAPACITY,
				   &data->full_avail_capacity);
		if (ret < 0) {
			LOG_ERR("Failed to read full available capacity");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_AVG_POWER:
		ret = cmd_reg_read(dev, BQ274XX_CMD_AVG_POWER, &data->avg_power);
		if (ret < 0) {
			LOG_ERR("Failed to read battery average power");
			return -EIO;
		}
		break;

	case SENSOR_CHAN_GAUGE_STATE_OF_HEALTH:
		ret = cmd_reg_read(dev, BQ274XX_CMD_SOH, &data->state_of_health);

		data->state_of_health = (data->state_of_health) & 0x00FF;

		if (ret < 0) {
			LOG_ERR("Failed to read state of health");
			return -EIO;
		}
		break;

	default:
		return -ENOTSUP;
	}

	return 0;
}

/**
 * @brief initialise the fuel gauge
 *
 * @return 0 for success
 */
static int gauge_init(const struct device *dev)
{
	const struct bq274xx_config *const config = dev->config;
	int ret = 0;
	uint16_t id;

	if (!device_is_ready(config->i2c.bus)) {
		LOG_ERR("I2C bus device not ready");
		return -ENODEV;
	}

#if defined(CONFIG_BQ274XX_PM) || defined(CONFIG_BQ274XX_TRIGGER)
	if (!device_is_ready(config->int_gpios.port)) {
		LOG_ERR("GPIO device pointer is not ready to be used");
		return -ENODEV;
	}
#endif

	ret = get_device_type(dev, &id);
	if (ret < 0) {
		LOG_ERR("Unable to get device ID");
		return -EIO;
	}

	if (id != BQ274XX_DEVICE_ID) {
		LOG_ERR("Invalid Device");
		return -EINVAL;
	}

#ifdef CONFIG_BQ274XX_TRIGGER
	ret = bq274xx_trigger_mode_init(dev);
	if (ret < 0) {
		LOG_ERR("Unable set up trigger mode.");
		return ret;
	}
#endif

	if (!config->lazy_loading) {
		ret = gauge_configure(dev);
	}

	return ret;
}

static int gauge_configure(const struct device *dev)
{
	const struct bq274xx_config *const config = dev->config;
	struct bq274xx_data *data = dev->data;

	int ret = 0;
	uint8_t tmp_checksum = 0, checksum_old = 0, checksum_new = 0;
	uint16_t flags = 0, designenergy_mwh = 0, taperrate = 0;
	uint8_t designcap_msb, designcap_lsb, designenergy_msb, designenergy_lsb,
		terminatevolt_msb, terminatevolt_lsb, taperrate_msb, taperrate_lsb;
	uint8_t block[32];

	designenergy_mwh = (uint16_t)3.7 * config->design_capacity;
	taperrate = (uint16_t)config->design_capacity / (0.1 * config->taper_current);

	/** Unseal the battery control register **/
	ret = ctrl_reg_write(dev, BQ274XX_UNSEAL_KEY);
	if (ret < 0) {
		LOG_ERR("Unable to unseal the battery");
		return -EIO;
	}

	ret = ctrl_reg_write(dev, BQ274XX_UNSEAL_KEY);
	if (ret < 0) {
		LOG_ERR("Unable to unseal the battery");
		return -EIO;
	}

	/* Send CFG_UPDATE */
	ret = ctrl_reg_write(dev, BQ274XX_CTRL_SET_CFGUPDATE);
	if (ret < 0) {
		LOG_ERR("Unable to set CFGUpdate");
		return -EIO;
	}

	/** Step to place the Gauge into CONFIG UPDATE Mode **/
	do {
		ret = cmd_reg_read(dev, BQ274XX_CMD_FLAGS, &flags);
		if (ret < 0) {
			LOG_ERR("Unable to read flags");
			return -EIO;
		}

		if (!(flags & 0x0010)) {
			k_msleep(BQ274XX_SUBCLASS_DELAY * 10);
		}

	} while (!(flags & 0x0010));

	ret = cmd_reg_write(dev, BQ274XX_EXT_DATA_CONTROL, 0x00);
	if (ret < 0) {
		LOG_ERR("Failed to enable block data memory");
		return -EIO;
	}

	/* Access State subclass */
	ret = cmd_reg_write(dev, BQ274XX_EXT_DATA_CLASS, 0x52);
	if (ret < 0) {
		LOG_ERR("Failed to update state subclass");
		return -EIO;
	}

	/* Write the block offset */
	ret = cmd_reg_write(dev, BQ274XX_EXT_DATA_BLOCK, 0x00);
	if (ret < 0) {
		LOG_ERR("Failed to update block offset");
		return -EIO;
	}

	for (uint8_t i = 0; i < 32; i++) {
		block[i] = 0;
	}

	ret = read_data_block(dev, 0x00, block, 32);
	if (ret < 0) {
		LOG_ERR("Unable to read block data");
		return -EIO;
	}

	tmp_checksum = 0;
	for (uint8_t i = 0; i < 32; i++) {
		tmp_checksum += block[i];
	}
	tmp_checksum = 255 - tmp_checksum;

	/* Read the block checksum */
	ret = i2c_reg_read_byte_dt(&config->i2c, BQ274XX_EXT_CHECKSUM, &checksum_old);
	if (ret < 0) {
		LOG_ERR("Unable to read block checksum");
		return -EIO;
	}

	designcap_msb = config->design_capacity >> 8;
	designcap_lsb = config->design_capacity & 0x00FF;
	designenergy_msb = designenergy_mwh >> 8;
	designenergy_lsb = designenergy_mwh & 0x00FF;
	terminatevolt_msb = config->terminate_voltage >> 8;
	terminatevolt_lsb = config->terminate_voltage & 0x00FF;
	taperrate_msb = taperrate >> 8;
	taperrate_lsb = taperrate & 0x00FF;

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_DESIGN_CAP_HIGH,
				    designcap_msb);
	if (ret < 0) {
		LOG_ERR("Failed to write designCAP MSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_DESIGN_CAP_LOW,
				    designcap_lsb);
	if (ret < 0) {
		LOG_ERR("Failed to write designCAP LSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_DESIGN_ENR_HIGH,
				    designenergy_msb);
	if (ret < 0) {
		LOG_ERR("Failed to write designEnergy MSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_DESIGN_ENR_LOW,
				    designenergy_lsb);
	if (ret < 0) {
		LOG_ERR("Failed to write designEnergy LSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_TERMINATE_VOLT_HIGH,
				    terminatevolt_msb);
	if (ret < 0) {
		LOG_ERR("Failed to write terminateVolt MSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_TERMINATE_VOLT_LOW,
				    terminatevolt_lsb);
	if (ret < 0) {
		LOG_ERR("Failed to write terminateVolt LSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_TAPERRATE_HIGH,
				    taperrate_msb);
	if (ret < 0) {
		LOG_ERR("Failed to write taperRate MSB");
		return -EIO;
	}

	ret = i2c_reg_write_byte_dt(&config->i2c, BQ274XX_EXT_BLKDAT_TAPERRATE_LOW, taperrate_lsb);
	if (ret < 0) {
		LOG_ERR("Failed to write taperRate LSB");
		return -EIO;
	}

	for (uint8_t i = 0; i < 32; i++) {
		block[i] = 0;
	}

	ret = read_data_block(dev, 0x00, block, 32);
	if (ret < 0) {
		LOG_ERR("Unable to read block data");
		return -EIO;
	}

	checksum_new = 0;
	for (uint8_t i = 0; i < 32; i++) {
		checksum_new += block[i];
	}
	checksum_new = 255 - checksum_new;

	ret = cmd_reg_write(dev, BQ274XX_EXT_CHECKSUM, checksum_new);
	if (ret < 0) {
		LOG_ERR("Failed to update new checksum");
		return -EIO;
	}

	tmp_checksum = 0;
	ret = i2c_reg_read_byte_dt(&config->i2c, BQ274XX_EXT_CHECKSUM, &tmp_checksum);
	if (ret < 0) {
		LOG_ERR("Failed to read checksum");
		return -EIO;
	}

	ret = ctrl_reg_write(dev, BQ274XX_CTRL_BAT_INSERT);
	if (ret < 0) {
		LOG_ERR("Unable to configure BAT Detect");
		return -EIO;
	}

	ret = ctrl_reg_write(dev, BQ274XX_CTRL_SOFT_RESET);
	if (ret < 0) {
		LOG_ERR("Failed to soft reset the gauge");
		return -EIO;
	}

	flags = 0;
	/* Poll Flags   */
	do {
		ret = cmd_reg_read(dev, BQ274XX_CMD_FLAGS, &flags);
		if (ret < 0) {
			LOG_ERR("Unable to read flags");
			return -EIO;
		}

		if (flags & 0x0010) {
			k_msleep(BQ274XX_SUBCLASS_DELAY * 10);
		}
	} while (flags & 0x0010);

	/* Seal the gauge */
	ret = ctrl_reg_write(dev, BQ274XX_CTRL_SEALED);
	if (ret < 0) {
		LOG_ERR("Failed to seal the gauge");
		return -EIO;
	}

	data->configured = true;

	return 0;
}

#ifdef CONFIG_BQ274XX_PM
static int enter_shutdown_mode(const struct device *dev)
{
	int ret;

	ret = ctrl_reg_write(dev, BQ274XX_UNSEAL_KEY);
	if (ret < 0) {
		LOG_ERR("Unable to unseal the battery");
		return ret;
	}

	ret = ctrl_reg_write(dev, BQ274XX_UNSEAL_KEY);
	if (ret < 0) {
		LOG_ERR("Unable to unseal the battery");
		return ret;
	}

	ret = ctrl_reg_write(dev, BQ274XX_CTRL_SHUTDOWN_ENABLE);
	if (ret < 0) {
		LOG_ERR("Unable to enable shutdown mode");
		return ret;
	}

	ret = ctrl_reg_write(dev, BQ274XX_CTRL_SHUTDOWN);
	if (ret < 0) {
		LOG_ERR("Unable to enter shutdown mode");
		return ret;
	}

	ret = ctrl_reg_write(dev, BQ274XX_CTRL_SEALED);
	if (ret < 0) {
		LOG_ERR("Failed to seal the gauge");
		return ret;
	}

	return 0;
}

static int exit_shutdown_mode(const struct device *dev)
{
	const struct bq274xx_config *const config = dev->config;
	int ret = 0;

	ret = gpio_pin_configure_dt(&config->int_gpios, GPIO_OUTPUT | GPIO_OPEN_DRAIN);
	if (ret < 0) {
		LOG_ERR("Unable to configure interrupt pin to output and open drain");
		return ret;
	}

	ret = gpio_pin_set_dt(&config->int_gpios, 0);
	if (ret < 0) {
		LOG_ERR("Unable to set interrupt pin to low");
		return ret;
	}

	k_msleep(PIN_DELAY_TIME);

	ret = gpio_pin_configure_dt(&config->int_gpios, GPIO_INPUT);
	if (ret < 0) {
		LOG_ERR("Unable to configure interrupt pin to input");
		return ret;
	}

	if (!config->lazy_loading) {
		k_msleep(INIT_TIME);

		ret = gauge_configure(dev);
		if (ret < 0) {
			LOG_ERR("Unable to configure bq274xx gauge");
			return ret;
		}
	}

	return 0;
}

static int pm_action(const struct device *dev, enum pm_device_action action)
{
	int ret;

	switch (action) {
	case PM_DEVICE_ACTION_TURN_OFF:
		ret = enter_shutdown_mode(dev);
		break;
	case PM_DEVICE_ACTION_RESUME:
		ret = exit_shutdown_mode(dev);
		break;
	default:
		ret = -ENOTSUP;
		break;
	}

	return ret;
}
#endif /* CONFIG_BQ274XX_PM */

static const struct sensor_driver_api bq274xx_battery_driver_api = {
	.sample_fetch = sample_fetch,
	.channel_get = channel_get,
#ifdef CONFIG_BQ274XX_TRIGGER
	.trigger_set = bq274xx_trigger_set,
#endif
};

#if defined(CONFIG_BQ274XX_PM) || defined(CONFIG_BQ274XX_TRIGGER)
#define BQ274XX_INT_CFG(index)							\
	.int_gpios = GPIO_DT_SPEC_INST_GET(index, int_gpios),
#define PM_BQ274XX_DT_INST_DEFINE(index, pm_action)				\
	PM_DEVICE_DT_INST_DEFINE(index, pm_action)
#define PM_BQ274XX_DT_INST_GET(index) PM_DEVICE_DT_INST_GET(index)
#else
#define BQ274XX_INT_CFG(index)
#define PM_BQ274XX_DT_INST_DEFINE(index, pm_action)
#define PM_BQ274XX_DT_INST_GET(index) NULL
#endif

#define BQ274XX_INIT(index)							\
	static struct bq274xx_data bq274xx_driver_##index;			\
										\
	static const struct bq274xx_config bq274xx_config_##index = {		\
		.i2c = I2C_DT_SPEC_INST_GET(index),				\
		BQ274XX_INT_CFG(index)						\
		.design_voltage = DT_INST_PROP(index, design_voltage),		\
		.design_capacity = DT_INST_PROP(index, design_capacity),	\
		.taper_current = DT_INST_PROP(index, taper_current),		\
		.terminate_voltage = DT_INST_PROP(index, terminate_voltage),	\
		.lazy_loading = DT_INST_PROP(index, zephyr_lazy_load),		\
	};									\
										\
	PM_BQ274XX_DT_INST_DEFINE(index, pm_action);				\
										\
	SENSOR_DEVICE_DT_INST_DEFINE(index, &gauge_init,			\
			    PM_BQ274XX_DT_INST_GET(index),			\
			    &bq274xx_driver_##index,				\
			    &bq274xx_config_##index, POST_KERNEL,		\
			    CONFIG_SENSOR_INIT_PRIORITY,			\
			    &bq274xx_battery_driver_api);

DT_INST_FOREACH_STATUS_OKAY(BQ274XX_INIT)
