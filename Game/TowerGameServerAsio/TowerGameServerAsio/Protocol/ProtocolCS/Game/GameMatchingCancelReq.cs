// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS.Game
{

using System;
using FlatBuffers;

public struct GameMatchingCancelReq : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static GameMatchingCancelReq GetRootAsGameMatchingCancelReq(ByteBuffer _bb) { return GetRootAsGameMatchingCancelReq(_bb, new GameMatchingCancelReq()); }
  public static GameMatchingCancelReq GetRootAsGameMatchingCancelReq(ByteBuffer _bb, GameMatchingCancelReq obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public GameMatchingCancelReq __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int GameServerID { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<GameMatchingCancelReq> CreateGameMatchingCancelReq(FlatBufferBuilder builder,
      int gameServerID = 0) {
    builder.StartObject(1);
    GameMatchingCancelReq.AddGameServerID(builder, gameServerID);
    return GameMatchingCancelReq.EndGameMatchingCancelReq(builder);
  }

  public static void StartGameMatchingCancelReq(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddGameServerID(FlatBufferBuilder builder, int gameServerID) { builder.AddInt(0, gameServerID, 0); }
  public static Offset<GameMatchingCancelReq> EndGameMatchingCancelReq(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<GameMatchingCancelReq>(o);
  }
};


}
