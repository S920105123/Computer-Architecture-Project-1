/* Funct code of R-format instructions, whose opcode==0x00. */
const int ADD   = 0x20,  ADDU  = 0x21,  SUB   = 0x22,
          AND   = 0x24,  OR    = 0x25,  XOR   = 0x26,
          NOR   = 0x27,  NAND  = 0x28,  SLT   = 0x2A,
          SLL   = 0x00,  SRL   = 0x02,  SRA   = 0x03,
          JR    = 0x08,  MULT  = 0x18,  MULTU = 0x19,
          MFHI  = 0x10,  MFLO  = 0x12;

/* Opcode of I-format instructions. */
const int ADDI  = 0x08,  ADDIU = 0x09,  LW    = 0x23,
          LH    = 0x21,  LHU   = 0x25,  LB    = 0x20,
          LBU   = 0x24,  SW    = 0x2B,  SH    = 0x29,
          SB    = 0x28,  LUI   = 0x0F,  ANDI  = 0x0C,
          ORI   = 0x0D,  NORI  = 0x0E,  SLTI  = 0x0A,
          BEQ   = 0x04,  BNE   = 0x05,  BGTZ  = 0x07;

/* Opcode of J-format and S-format instructions. */
const int J     = 0x02,  JAL   = 0x03,  HALT  = 0x3F;
