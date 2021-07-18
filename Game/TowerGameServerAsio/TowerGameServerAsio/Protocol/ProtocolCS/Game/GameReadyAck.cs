// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS.Game
{

using System;
using FlatBuffers;

public struct GameReadyAck : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static GameReadyAck GetRootAsGameReadyAck(ByteBuffer _bb) { return GetRootAsGameReadyAck(_bb, new GameReadyAck()); }
  public static GameReadyAck GetRootAsGameReadyAck(ByteBuffer _bb, GameReadyAck obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public GameReadyAck __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<GameReadyAck> CreateGameReadyAck(FlatBufferBuilder builder,
      int result = 0) {
    builder.StartObject(1);
    GameReadyAck.AddResult(builder, result);
    return GameReadyAck.EndGameReadyAck(builder);
  }

  public static void StartGameReadyAck(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static Offset<GameReadyAck> EndGameReadyAck(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GameReadyAck>(o);
  }
};


}