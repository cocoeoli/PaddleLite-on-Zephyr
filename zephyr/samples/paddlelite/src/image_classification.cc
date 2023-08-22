#include <iostream>
#include <vector>
#include "paddle_api.h"
using namespace std;
#include <zephyr/kernel.h>
#include <zephyr/timing/timing.h>
using namespace paddle::lite_api;  // NOLINT
#define  LITE_WITH_ARM
int64_t ShapeProduction(const shape_t& shape) {
  int64_t res = 1;
  for (auto i : shape) res *= i;
  return res;
}

void RunModel() {
std::string model_dir = " ";
MobileConfig config;
config.set_model_from_file(model_dir);
std::shared_ptr<PaddlePredictor> predictor =
    CreatePaddlePredictor<MobileConfig>(config);
  // 3. Prepare input data
  std::unique_ptr<Tensor> input_tensor(std::move(predictor->GetInput(0)));
  input_tensor->Resize({1, 3, 224, 224});
  auto* data = input_tensor->mutable_data<float>();
  for (int i = 0; i < ShapeProduction(input_tensor->shape()); ++i) {
    data[i] = 1;
  }
  // 4. Run predictor
  predictor->Run();
  // 5. Get output
  std::unique_ptr<const Tensor> output_tensor(
      std::move(predictor->GetOutput(0)));
  std::cout << "Output shape " << output_tensor->shape()[1] << std::endl;
  for (int i = 0; i < ShapeProduction(output_tensor->shape()); i += 100) {
    std::cout << "Output[" << i << "]: " << output_tensor->data<float>()[i]
              << std::endl;
  }
  
}

int main(void) {
  timing_t start_time, end_time;  //开始时间，结束时间
  uint64_t total_cycles;   //计时器周期数
  uint64_t total_ns;    //纳秒总时间
  timing_init();
  timing_start();
  start_time = timing_counter_get();
  RunModel();
  end_time = timing_counter_get();
  total_cycles = timing_cycles_get(&start_time, &end_time);
  total_ns = timing_cycles_to_ns(total_cycles);
  timing_stop();
  cout<<"total_ns is "<<total_ns<<endl;
  return 0;
}
