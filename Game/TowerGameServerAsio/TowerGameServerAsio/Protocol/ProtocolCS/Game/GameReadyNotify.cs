// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS.Game
{

using System;
using FlatBuffers;

public struct GameReadyNotify : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static GameReadyNotify GetRootAsGameReadyNotify(ByteBuffer _bb) { return GetRootAsGameReadyNotify(_bb, new GameReadyNotify()); }
  public static GameReadyNotify GetRootAsGameReadyNotify(ByteBuffer _bb, GameReadyNotify obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public GameReadyNotify __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int GroupHostID { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public ProtocolCS.playerInfo? PlayerInfos(int j) { int o = __p.__offset(6); return o != 0 ? (ProtocolCS.playerInfo?)(new ProtocolCS.playerInfo()).__assign(__p.__indirect(__p.__vector(o) + j * 4), __p.bb) : null; }
  public int PlayerInfosLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }

  public static Offset<GameReadyNotify> CreateGameReadyNotify(FlatBufferBuilder builder,
      int groupHostID = 0,
      VectorOffset playerInfosOffset = default(VectorOffset)) {
    builder.StartObject(2);
    GameReadyNotify.AddPlayerInfos(builder, playerInfosOffset);
    GameReadyNotify.AddGroupHostID(builder, groupHostID);
    return GameReadyNotify.EndGameReadyNotify(builder);
  }

  public static void StartGameReadyNotify(FlatBufferBuilder builder) { builder.StartObject(2); }
  public static void AddGroupHostID(FlatBufferBuilder builder, int groupHostID) { builder.AddInt(0, groupHostID, 0); }
  public static void AddPlayerInfos(FlatBufferBuilder builder, VectorOffset playerInfosOffset) { builder.AddOffset(1, playerInfosOffset.Value, 0); }
  public static VectorOffset CreatePlayerInfosVector(FlatBufferBuilder builder, Offset<ProtocolCS.playerInfo>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartPlayerInfosVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static Offset<GameReadyNotify> EndGameReadyNotify(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GameReadyNotify>(o);
  }
};


}
