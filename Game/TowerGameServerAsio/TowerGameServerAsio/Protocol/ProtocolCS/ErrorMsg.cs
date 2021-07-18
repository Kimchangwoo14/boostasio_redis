// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS
{

using System;
using FlatBuffers;

public struct ErrorMsg : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static ErrorMsg GetRootAsErrorMsg(ByteBuffer _bb) { return GetRootAsErrorMsg(_bb, new ErrorMsg()); }
  public static ErrorMsg GetRootAsErrorMsg(ByteBuffer _bb, ErrorMsg obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public ErrorMsg __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public ProtocolCS.E_ErrorResult Result { get { int o = __p.__offset(4); return o != 0 ? (ProtocolCS.E_ErrorResult)__p.bb.GetInt(o + __p.bb_pos) : ProtocolCS.E_ErrorResult.INVAILD_USERID; } }

  public static Offset<ErrorMsg> CreateErrorMsg(FlatBufferBuilder builder,
      ProtocolCS.E_ErrorResult result = ProtocolCS.E_ErrorResult.INVAILD_USERID) {
    builder.StartObject(1);
    ErrorMsg.AddResult(builder, result);
    return ErrorMsg.EndErrorMsg(builder);
  }

  public static void StartErrorMsg(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddResult(FlatBufferBuilder builder, ProtocolCS.E_ErrorResult result) { builder.AddInt(0, (int)result, 0); }
  public static Offset<ErrorMsg> EndErrorMsg(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<ErrorMsg>(o);
  }
};


}
