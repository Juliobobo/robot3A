const
  pi : real;
  kp_teta : real;
  ki_teta : real;
  
node comportement
  (Cg: real;
  Cd: real;
  mode: bool)
returns
  (u_d: real;
  u_g: real);

var
  V11_w_001: real;
  V13_w_003: real;
  V14_w_004: real;
  V17_w_007: real;
  V19_w_009: real;
  V117_w_004: real;
  V140_w_003: real;
  V141_w_004: real;
  V142_w_005: real;
  V143_w_006: real;
  V144_w_007: real;
  V145_w_008: real;
  V146_w_009: real;
  V147_w_011: real;
  V148_w_012: real;
  V149_w_013: real;
  V150_w_014: real;
  V151_w_015: real;
  V152_w_016: real;

let
  u_d = (if mode then V14_w_004 else V11_w_001);
  u_g = (if mode then V13_w_003 else 0.400000);
  V11_w_001 = (-1.000000 * 0.400000);
  V13_w_003 = ((1.000000 / 2.000000) * V149_w_013);
  V14_w_004 = ((1.000000 / 2.000000) * V150_w_014);
  V17_w_007 = ((pi / 200.000000) * V117_w_004);
  V19_w_009 = (Cd + Cg);
  V117_w_004 = (Cd - Cg);
  V140_w_003 = (0.000000 -> (pre V141_w_004));
  V141_w_004 = (V142_w_005 + V140_w_003);
  V142_w_005 = (0.002000 * V17_w_007);
  V143_w_006 = (V152_w_016 + V151_w_015);
  V144_w_007 = ((-V146_w_009) + V147_w_011);
  V145_w_008 = (2.000000 * V144_w_007);
  V146_w_009 = (if (V148_w_012 < 0.000000) then (-V148_w_012) else V148_w_012);
  V147_w_011 = (0.005000 * V19_w_009);
  V148_w_012 = (2.000000 * V143_w_006);
  V149_w_013 = ((-V143_w_006) + V145_w_008);
  V150_w_014 = (V143_w_006 + V145_w_008);
  V151_w_015 = (kp_teta * V17_w_007);
  V152_w_016 = (ki_teta * V141_w_004);
tel

