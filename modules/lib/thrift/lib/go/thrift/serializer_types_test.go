/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

package thrift

// Autogenerated by Thrift Compiler (FIXME)
// DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING

/* THE FOLLOWING THRIFT FILE WAS USED TO CREATE THIS

enum MyTestEnum {
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
}

struct MyTestStruct {
	1: bool on,
	2: byte b,
	3: i16 int16,
	4: i32 int32,
	5: i64 int64,
	6: double d,
	7: string st,
	8: binary bin,
	9: map<string, string> stringMap,
	10: list<string> stringList,
	11: set<string> stringSet,
	12: MyTestEnum e,
}
*/

import (
	"context"
	"fmt"
)

// (needed to ensure safety because of naive import list construction.)
var _ = ZERO
var _ = fmt.Printf

var GoUnusedProtection__ int

type MyTestEnum int64

const (
	MyTestEnum_FIRST  MyTestEnum = 1
	MyTestEnum_SECOND MyTestEnum = 2
	MyTestEnum_THIRD  MyTestEnum = 3
	MyTestEnum_FOURTH MyTestEnum = 4
)

func (p MyTestEnum) String() string {
	switch p {
	case MyTestEnum_FIRST:
		return "FIRST"
	case MyTestEnum_SECOND:
		return "SECOND"
	case MyTestEnum_THIRD:
		return "THIRD"
	case MyTestEnum_FOURTH:
		return "FOURTH"
	}
	return "<UNSET>"
}

func MyTestEnumFromString(s string) (MyTestEnum, error) {
	switch s {
	case "FIRST":
		return MyTestEnum_FIRST, nil
	case "SECOND":
		return MyTestEnum_SECOND, nil
	case "THIRD":
		return MyTestEnum_THIRD, nil
	case "FOURTH":
		return MyTestEnum_FOURTH, nil
	}
	return MyTestEnum(0), fmt.Errorf("not a valid MyTestEnum string")
}

func MyTestEnumPtr(v MyTestEnum) *MyTestEnum { return &v }

type MyTestStruct struct {
	On         bool                `thrift:"on,1" json:"on"`
	B          int8                `thrift:"b,2" json:"b"`
	Int16      int16               `thrift:"int16,3" json:"int16"`
	Int32      int32               `thrift:"int32,4" json:"int32"`
	Int64      int64               `thrift:"int64,5" json:"int64"`
	D          float64             `thrift:"d,6" json:"d"`
	St         string              `thrift:"st,7" json:"st"`
	Bin        []byte              `thrift:"bin,8" json:"bin"`
	StringMap  map[string]string   `thrift:"stringMap,9" json:"stringMap"`
	StringList []string            `thrift:"stringList,10" json:"stringList"`
	StringSet  map[string]struct{} `thrift:"stringSet,11" json:"stringSet"`
	E          MyTestEnum          `thrift:"e,12" json:"e"`
}

func NewMyTestStruct() *MyTestStruct {
	return &MyTestStruct{}
}

func (p *MyTestStruct) GetOn() bool {
	return p.On
}

func (p *MyTestStruct) GetB() int8 {
	return p.B
}

func (p *MyTestStruct) GetInt16() int16 {
	return p.Int16
}

func (p *MyTestStruct) GetInt32() int32 {
	return p.Int32
}

func (p *MyTestStruct) GetInt64() int64 {
	return p.Int64
}

func (p *MyTestStruct) GetD() float64 {
	return p.D
}

func (p *MyTestStruct) GetSt() string {
	return p.St
}

func (p *MyTestStruct) GetBin() []byte {
	return p.Bin
}

func (p *MyTestStruct) GetStringMap() map[string]string {
	return p.StringMap
}

func (p *MyTestStruct) GetStringList() []string {
	return p.StringList
}

func (p *MyTestStruct) GetStringSet() map[string]struct{} {
	return p.StringSet
}

func (p *MyTestStruct) GetE() MyTestEnum {
	return p.E
}
func (p *MyTestStruct) Read(ctx context.Context, iprot TProtocol) error {
	if _, err := iprot.ReadStructBegin(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T read error: ", p), err)
	}
	for {
		_, fieldTypeId, fieldId, err := iprot.ReadFieldBegin(ctx)
		if err != nil {
			return PrependError(fmt.Sprintf("%T field %d read error: ", p, fieldId), err)
		}
		if fieldTypeId == STOP {
			break
		}
		switch fieldId {
		case 1:
			if err := p.readField1(ctx, iprot); err != nil {
				return err
			}
		case 2:
			if err := p.readField2(ctx, iprot); err != nil {
				return err
			}
		case 3:
			if err := p.readField3(ctx, iprot); err != nil {
				return err
			}
		case 4:
			if err := p.readField4(ctx, iprot); err != nil {
				return err
			}
		case 5:
			if err := p.readField5(ctx, iprot); err != nil {
				return err
			}
		case 6:
			if err := p.readField6(ctx, iprot); err != nil {
				return err
			}
		case 7:
			if err := p.readField7(ctx, iprot); err != nil {
				return err
			}
		case 8:
			if err := p.readField8(ctx, iprot); err != nil {
				return err
			}
		case 9:
			if err := p.readField9(ctx, iprot); err != nil {
				return err
			}
		case 10:
			if err := p.readField10(ctx, iprot); err != nil {
				return err
			}
		case 11:
			if err := p.readField11(ctx, iprot); err != nil {
				return err
			}
		case 12:
			if err := p.readField12(ctx, iprot); err != nil {
				return err
			}
		default:
			if err := iprot.Skip(ctx, fieldTypeId); err != nil {
				return err
			}
		}
		if err := iprot.ReadFieldEnd(ctx); err != nil {
			return err
		}
	}
	if err := iprot.ReadStructEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T read struct end error: ", p), err)
	}
	return nil
}

func (p *MyTestStruct) readField1(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadBool(ctx); err != nil {
		return PrependError("error reading field 1: ", err)
	} else {
		p.On = v
	}
	return nil
}

func (p *MyTestStruct) readField2(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadByte(ctx); err != nil {
		return PrependError("error reading field 2: ", err)
	} else {
		temp := int8(v)
		p.B = temp
	}
	return nil
}

func (p *MyTestStruct) readField3(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadI16(ctx); err != nil {
		return PrependError("error reading field 3: ", err)
	} else {
		p.Int16 = v
	}
	return nil
}

func (p *MyTestStruct) readField4(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadI32(ctx); err != nil {
		return PrependError("error reading field 4: ", err)
	} else {
		p.Int32 = v
	}
	return nil
}

func (p *MyTestStruct) readField5(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadI64(ctx); err != nil {
		return PrependError("error reading field 5: ", err)
	} else {
		p.Int64 = v
	}
	return nil
}

func (p *MyTestStruct) readField6(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadDouble(ctx); err != nil {
		return PrependError("error reading field 6: ", err)
	} else {
		p.D = v
	}
	return nil
}

func (p *MyTestStruct) readField7(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadString(ctx); err != nil {
		return PrependError("error reading field 7: ", err)
	} else {
		p.St = v
	}
	return nil
}

func (p *MyTestStruct) readField8(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadBinary(ctx); err != nil {
		return PrependError("error reading field 8: ", err)
	} else {
		p.Bin = v
	}
	return nil
}

func (p *MyTestStruct) readField9(ctx context.Context, iprot TProtocol) error {
	_, _, size, err := iprot.ReadMapBegin(ctx)
	if err != nil {
		return PrependError("error reading map begin: ", err)
	}
	tMap := make(map[string]string, size)
	p.StringMap = tMap
	for i := 0; i < size; i++ {
		var _key0 string
		if v, err := iprot.ReadString(ctx); err != nil {
			return PrependError("error reading field 0: ", err)
		} else {
			_key0 = v
		}
		var _val1 string
		if v, err := iprot.ReadString(ctx); err != nil {
			return PrependError("error reading field 0: ", err)
		} else {
			_val1 = v
		}
		p.StringMap[_key0] = _val1
	}
	if err := iprot.ReadMapEnd(ctx); err != nil {
		return PrependError("error reading map end: ", err)
	}
	return nil
}

func (p *MyTestStruct) readField10(ctx context.Context, iprot TProtocol) error {
	_, size, err := iprot.ReadListBegin(ctx)
	if err != nil {
		return PrependError("error reading list begin: ", err)
	}
	tSlice := make([]string, 0, size)
	p.StringList = tSlice
	for i := 0; i < size; i++ {
		var _elem2 string
		if v, err := iprot.ReadString(ctx); err != nil {
			return PrependError("error reading field 0: ", err)
		} else {
			_elem2 = v
		}
		p.StringList = append(p.StringList, _elem2)
	}
	if err := iprot.ReadListEnd(ctx); err != nil {
		return PrependError("error reading list end: ", err)
	}
	return nil
}

func (p *MyTestStruct) readField11(ctx context.Context, iprot TProtocol) error {
	_, size, err := iprot.ReadSetBegin(ctx)
	if err != nil {
		return PrependError("error reading set begin: ", err)
	}
	tSet := make(map[string]struct{}, size)
	p.StringSet = tSet
	for i := 0; i < size; i++ {
		var _elem3 string
		if v, err := iprot.ReadString(ctx); err != nil {
			return PrependError("error reading field 0: ", err)
		} else {
			_elem3 = v
		}
		p.StringSet[_elem3] = struct{}{}
	}
	if err := iprot.ReadSetEnd(ctx); err != nil {
		return PrependError("error reading set end: ", err)
	}
	return nil
}

func (p *MyTestStruct) readField12(ctx context.Context, iprot TProtocol) error {
	if v, err := iprot.ReadI32(ctx); err != nil {
		return PrependError("error reading field 12: ", err)
	} else {
		temp := MyTestEnum(v)
		p.E = temp
	}
	return nil
}

func (p *MyTestStruct) Write(ctx context.Context, oprot TProtocol) error {
	if err := oprot.WriteStructBegin(ctx, "MyTestStruct"); err != nil {
		return PrependError(fmt.Sprintf("%T write struct begin error: ", p), err)
	}
	if err := p.writeField1(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField2(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField3(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField4(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField5(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField6(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField7(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField8(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField9(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField10(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField11(ctx, oprot); err != nil {
		return err
	}
	if err := p.writeField12(ctx, oprot); err != nil {
		return err
	}
	if err := oprot.WriteFieldStop(ctx); err != nil {
		return PrependError("write field stop error: ", err)
	}
	if err := oprot.WriteStructEnd(ctx); err != nil {
		return PrependError("write struct stop error: ", err)
	}
	return nil
}

func (p *MyTestStruct) writeField1(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "on", BOOL, 1); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 1:on: ", p), err)
	}
	if err := oprot.WriteBool(ctx, bool(p.On)); err != nil {
		return PrependError(fmt.Sprintf("%T.on (1) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 1:on: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField2(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "b", BYTE, 2); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 2:b: ", p), err)
	}
	if err := oprot.WriteByte(ctx, int8(p.B)); err != nil {
		return PrependError(fmt.Sprintf("%T.b (2) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 2:b: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField3(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "int16", I16, 3); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 3:int16: ", p), err)
	}
	if err := oprot.WriteI16(ctx, int16(p.Int16)); err != nil {
		return PrependError(fmt.Sprintf("%T.int16 (3) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 3:int16: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField4(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "int32", I32, 4); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 4:int32: ", p), err)
	}
	if err := oprot.WriteI32(ctx, int32(p.Int32)); err != nil {
		return PrependError(fmt.Sprintf("%T.int32 (4) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 4:int32: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField5(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "int64", I64, 5); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 5:int64: ", p), err)
	}
	if err := oprot.WriteI64(ctx, int64(p.Int64)); err != nil {
		return PrependError(fmt.Sprintf("%T.int64 (5) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 5:int64: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField6(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "d", DOUBLE, 6); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 6:d: ", p), err)
	}
	if err := oprot.WriteDouble(ctx, float64(p.D)); err != nil {
		return PrependError(fmt.Sprintf("%T.d (6) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 6:d: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField7(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "st", STRING, 7); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 7:st: ", p), err)
	}
	if err := oprot.WriteString(ctx, string(p.St)); err != nil {
		return PrependError(fmt.Sprintf("%T.st (7) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 7:st: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField8(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "bin", STRING, 8); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 8:bin: ", p), err)
	}
	if err := oprot.WriteBinary(ctx, p.Bin); err != nil {
		return PrependError(fmt.Sprintf("%T.bin (8) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 8:bin: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField9(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "stringMap", MAP, 9); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 9:stringMap: ", p), err)
	}
	if err := oprot.WriteMapBegin(ctx, STRING, STRING, len(p.StringMap)); err != nil {
		return PrependError("error writing map begin: ", err)
	}
	for k, v := range p.StringMap {
		if err := oprot.WriteString(ctx, string(k)); err != nil {
			return PrependError(fmt.Sprintf("%T. (0) field write error: ", p), err)
		}
		if err := oprot.WriteString(ctx, string(v)); err != nil {
			return PrependError(fmt.Sprintf("%T. (0) field write error: ", p), err)
		}
	}
	if err := oprot.WriteMapEnd(ctx); err != nil {
		return PrependError("error writing map end: ", err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 9:stringMap: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField10(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "stringList", LIST, 10); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 10:stringList: ", p), err)
	}
	if err := oprot.WriteListBegin(ctx, STRING, len(p.StringList)); err != nil {
		return PrependError("error writing list begin: ", err)
	}
	for _, v := range p.StringList {
		if err := oprot.WriteString(ctx, string(v)); err != nil {
			return PrependError(fmt.Sprintf("%T. (0) field write error: ", p), err)
		}
	}
	if err := oprot.WriteListEnd(ctx); err != nil {
		return PrependError("error writing list end: ", err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 10:stringList: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField11(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "stringSet", SET, 11); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 11:stringSet: ", p), err)
	}
	if err := oprot.WriteSetBegin(ctx, STRING, len(p.StringSet)); err != nil {
		return PrependError("error writing set begin: ", err)
	}
	for v := range p.StringSet {
		if err := oprot.WriteString(ctx, string(v)); err != nil {
			return PrependError(fmt.Sprintf("%T. (0) field write error: ", p), err)
		}
	}
	if err := oprot.WriteSetEnd(ctx); err != nil {
		return PrependError("error writing set end: ", err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 11:stringSet: ", p), err)
	}
	return err
}

func (p *MyTestStruct) writeField12(ctx context.Context, oprot TProtocol) (err error) {
	if err := oprot.WriteFieldBegin(ctx, "e", I32, 12); err != nil {
		return PrependError(fmt.Sprintf("%T write field begin error 12:e: ", p), err)
	}
	if err := oprot.WriteI32(ctx, int32(p.E)); err != nil {
		return PrependError(fmt.Sprintf("%T.e (12) field write error: ", p), err)
	}
	if err := oprot.WriteFieldEnd(ctx); err != nil {
		return PrependError(fmt.Sprintf("%T write field end error 12:e: ", p), err)
	}
	return err
}

func (p *MyTestStruct) String() string {
	if p == nil {
		return "<nil>"
	}
	return fmt.Sprintf("MyTestStruct(%+v)", *p)
}
