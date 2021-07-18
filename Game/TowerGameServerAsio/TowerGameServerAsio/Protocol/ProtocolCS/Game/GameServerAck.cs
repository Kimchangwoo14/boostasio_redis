// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS.Game
{

using System;
using FlatBuffers;

public struct GameServerAck : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static GameServerAck GetRootAsGameServerAck(ByteBuffer _bb) { return GetRootAsGameServerAck(_bb, new GameServerAck()); }
  public static GameServerAck GetRootAsGameServerAck(ByteBuffer _bb, GameServerAck obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public GameServerAck __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public string Data { get { int o = __p.__offset(6); return o != 0 ? __p.__string(o + __p.bb_pos) : null; } }
  public ArraySegment<byte>? GetDataBytes() { return __p.__vector_as_arraysegment(6); }

  public static Offset<GameServerAck> CreateGameServerAck(FlatBufferBuilder builder,
      int result = 0,
      StringOffset DataOffset = default(StringOffset)) {
    builder.StartObject(2);
    GameServerAck.AddData(builder, DataOffset);
    GameServerAck.AddResult(builder, result);
    return GameServerAck.EndGameServerAck(builder);
  }

  public static void StartGameServerAck(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static void AddData(FlatBufferBuilder builder, StringOffset DataOffset) { builder.AddOffset(1, DataOffset.Value, 0); }
  public static Offset<GameServerAck> EndGameServerAck(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GameServerAck>(o);
  }
};


}