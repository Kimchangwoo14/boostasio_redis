// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS.Game
{

using System;
using FlatBuffers;

public struct GameMatchingCancelNotify : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static GameMatchingCancelNotify GetRootAsGameMatchingCancelNotify(ByteBuffer _bb) { return GetRootAsGameMatchingCancelNotify(_bb, new GameMatchingCancelNotify()); }
  public static GameMatchingCancelNotify GetRootAsGameMatchingCancelNotify(ByteBuffer _bb, GameMatchingCancelNotify obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public GameMatchingCancelNotify __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Result { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<GameMatchingCancelNotify> CreateGameMatchingCancelNotify(FlatBufferBuilder builder,
      int result = 0) {
    builder.StartObject(1);
    GameMatchingCancelNotify.AddResult(builder, result);
    return GameMatchingCancelNotify.EndGameMatchingCancelNotify(builder);
  }

  public static void StartGameMatchingCancelNotify(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddResult(FlatBufferBuilder builder, int result) { builder.AddInt(0, result, 0); }
  public static Offset<GameMatchingCancelNotify> EndGameMatchingCancelNotify(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GameMatchingCancelNotify>(o);
  }
};


}
