// automatically generated by the FlatBuffers compiler, do not modify

namespace ProtocolCS.Room
{

using System;
using FlatBuffers;

public struct SellTowerReq : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static SellTowerReq GetRootAsSellTowerReq(ByteBuffer _bb) { return GetRootAsSellTowerReq(_bb, new SellTowerReq()); }
  public static SellTowerReq GetRootAsSellTowerReq(ByteBuffer _bb, SellTowerReq obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public SellTowerReq __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public long AccountUID { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetLong(o + __p.bb_pos) : (long)0; } }
  public int PosX { get { int o = __p.__offset(6); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int PosY { get { int o = __p.__offset(8); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }
  public int ObjectID { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<SellTowerReq> CreateSellTowerReq(FlatBufferBuilder builder,
      long accountUID = 0,
      int posX = 0,
      int posY = 0,
      int objectID = 0) {
    builder.StartObject(4);
    SellTowerReq.AddAccountUID(builder, accountUID);
    SellTowerReq.AddObjectID(builder, objectID);
    SellTowerReq.AddPosY(builder, posY);
    SellTowerReq.AddPosX(builder, posX);
    return SellTowerReq.EndSellTowerReq(builder);
  }

  public static void StartSellTowerReq(FlatBufferBuilder builder) { builder.StartObject(4); }
  public static void AddAccountUID(FlatBufferBuilder builder, long accountUID) { builder.AddLong(0, accountUID, 0); }
  public static void AddPosX(FlatBufferBuilder builder, int posX) { builder.AddInt(1, posX, 0); }
  public static void AddPosY(FlatBufferBuilder builder, int posY) { builder.AddInt(2, posY, 0); }
  public static void AddObjectID(FlatBufferBuilder builder, int objectID) { builder.AddInt(3, objectID, 0); }
  public static Offset<SellTowerReq> EndSellTowerReq(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<SellTowerReq>(o);
  }
};


}