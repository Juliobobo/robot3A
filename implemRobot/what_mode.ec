const
  distanceMin : real;
  
node what_mode
  (Cd: real;
  distance: real)
returns
  (Mode: bool);

var
  V6_w_000: bool;
  V7_w_001: bool;
  V8_w_002: bool;
  V9_w_003: bool;
  V10_w_004: bool;
  V11_w_005: bool;
  V12_w_006: bool;
  V13_w_007: bool;
  V14_w_008: bool;
  V16_w_010: bool;
  V18_w_012: bool;
  V101_w_000: bool;
  V102_w_003: bool;
  V103_w_005: bool;
  V104_w_006: bool;
  V105_w_007: bool;
  V106_w_008: bool;
  V116_w_000: bool;
  V117_w_004: bool;
  V118_w_005: bool;
  V130_w_000: bool;
  V131_w_004: bool;
  V132_w_005: bool;
  V144_w_000: bool;
  V145_w_004: bool;
  V146_w_005: bool;

let
  Mode = (not V18_w_012);
  V6_w_000 = (false -> (pre V7_w_001));
  V7_w_001 = (V146_w_005 and V144_w_000);
  V8_w_002 = (V13_w_007 and V9_w_003);
  V9_w_003 = (V118_w_005 and V116_w_000);
  V10_w_004 = (V12_w_006 and V11_w_005);
  V11_w_005 = (V16_w_010 and V18_w_012);
  V12_w_006 = (V132_w_005 and V130_w_000);
  V13_w_007 = (V14_w_008 and V18_w_012);
  V14_w_008 = (Cd > 50.000000);
  V16_w_010 = (Cd < 50.000000);
  V18_w_012 = (V104_w_006 <> V105_w_007);
  V101_w_000 = (distance < distanceMin);
  V102_w_003 = (V101_w_000 or V6_w_000);
  V103_w_005 = (not V106_w_008);
  V104_w_006 = (V102_w_003 and V103_w_005);
  V105_w_007 = (false -> (pre V18_w_012));
  V106_w_008 = (false -> (pre V102_w_003));
  V116_w_000 = (not V6_w_000);
  V117_w_004 = (false -> (pre V9_w_003));
  V118_w_005 = (V117_w_004 or V10_w_004);
  V130_w_000 = (not V6_w_000);
  V131_w_004 = (false -> (pre V12_w_006));
  V132_w_005 = (V131_w_004 or V13_w_007);
  V144_w_000 = (not V6_w_000);
  V145_w_004 = (false -> (pre V7_w_001));
  V146_w_005 = (V145_w_004 or V8_w_002);
tel

