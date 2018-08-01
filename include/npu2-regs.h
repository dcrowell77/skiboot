/* Copyright 2013-2016 IBM Corp.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NPU2_REGS_H
#define __NPU2_REGS_H

struct npu2;
uint64_t npu2_read4(struct npu2 *p, uint64_t reg);
void npu2_write4(struct npu2 *p, uint64_t reg, uint64_t val);
uint64_t npu2_read(struct npu2 *p, uint64_t reg);
void npu2_write(struct npu2 *p, uint64_t reg, uint64_t val);
void npu2_write_mask(struct npu2 *p, uint64_t reg, uint64_t val, uint64_t mask);
uint64_t npu2_scom_read(uint64_t gcid, uint64_t scom_base,
			uint64_t reg, uint64_t size);
void npu2_scom_write(uint64_t gcid, uint64_t scom_base,
		     uint64_t reg, uint64_t size,
		     uint64_t val);

/* These aren't really NPU specific registers but we initialise them in NPU
 * code */
#define MCD0_BANK0_CN3 0x301100d
#define MCD1_BANK0_CN3 0x301140d
#define	MCD_BANK_CN_VALID	PPC_BIT(0)
#define	MCD_BANK_CN_SIZE	PPC_BITMASK(13,29)
#define	MCD_BANK_CN_ADDR	PPC_BITMASK(33,63)
#define PB_CENT_MODE		0x5011c0a
#define  PB_CFG_CHIP_ADDR_EXTENSION_MASK_CENT PPC_BITMASK(42,48)


#define NPU2_REG_OFFSET(stack, block, offset) \
	(((stack) << 20) | ((block) << 16) | (offset))

#define NPU2_NTL_REG_OFFSET(ndev, offset)				\
	NPU2_REG_OFFSET(NPU2_STACK_STCK_0 + ((ndev)->index >> 1),       \
			NPU2_BLOCK_NTL0 + ((ndev)->index % 2)*2, offset)

#define NPU2_NTLU_REG_OFFSET(ndev, offset)				\
	NPU2_REG_OFFSET(NPU2_STACK_STCK_0U + ((ndev)->index >> 1),       \
			NPU2_BLOCK_NTL0 + ((ndev)->index % 2)*2, offset)

#define NPU2_DL_REG_OFFSET(ndev, offset)	\
	NPU2_REG_OFFSET(((ndev)->index >> 1),				\
			8 + ((ndev)->index % 2)*2, offset)

#define NPU2_SM_REG_OFFSET(ndev, sm, offset)				\
	NPU2_REG_OFFSET(NPU2_STACK_STCK_0 + ((ndev)->index >> 1),	\
			NPU2_BLOCK_SM_0 + (sm), offset)

/* Get the offset for this register */
#define NPU2_REG(reg) \
	((reg) & 0xffff)

/* Get the stack number for this register */
#define NPU2_REG_STACK(reg) \
	(((reg) >> 20) & 0xf)

/* XTS tables */
#define NPU2_XTS_BDF_MAP_SIZE	16
#define NPU2_XTS_PID_MAP_SIZE	256

/* Stacks */
#define NPU2_STACK_STCK_0U	0x0
#define NPU2_STACK_STCK_1U	0x1
#define NPU2_STACK_STCK_2U	0x2
#define NPU2_STACK_STCK_0     	0x4
#define NPU2_STACK_STCK_1     	0x5
#define NPU2_STACK_STCK_2     	0x6
#define NPU2_STACK_MISC		0x7
#define NPU2_STACK_ATSD		0x8
#define NPU2_STACK_PHY00	0xc
#define NPU2_STACK_PHY01	0xd
#define NPU2_STACK_PHY10	0xe
#define NPU2_STACK_PHY11	0xf

/* Link stack blocks */
#define NPU2_BLOCK_SM_0	0x0
#define NPU2_BLOCK_SM_1 0x1
#define NPU2_BLOCK_SM_2 0x2
#define NPU2_BLOCK_SM_3 0x3
#define NPU2_BLOCK_CTL	0x4
#define NPU2_BLOCK_DAT	0x5
#define NPU2_BLOCK_NTL0	0x9
#define NPU2_BLOCK_NTL1	0xb
#define NPU2_BLOCK_OTL0 0xc
#define NPU2_BLOCK_OTL1 0xd

/* OpenCAPI blocks */
#define NPU2_BLOCK_XSL 0xe

/* MISC stack blocks */
#define NPU2_BLOCK_ATS	0
#define NPU2_BLOCK_XTS	1
#define NPU2_BLOCK_MISC 2

/* ATSD stack blocks */
#define NPU2_BLOCK_ATSD0	0
#define NPU2_BLOCK_ATSD1	1
#define NPU2_BLOCK_ATSD2	2
#define NPU2_BLOCK_ATSD3	3
#define NPU2_BLOCK_ATSD4	4
#define NPU2_BLOCK_ATSD5	5
#define NPU2_BLOCK_ATSD6	6
#define NPU2_BLOCK_ATSD7	7

/* SM block registers */
#define NPU2_CQ_SM_MISC_CFG0			0x000
#define   NPU2_CQ_SM_MISC_CFG0_CONFIG_ENABLE_PBUS PPC_BIT(38)
#define   NPU2_CQ_SM_MISC_CFG0_CONFIG_OCAPI_MODE PPC_BIT(57)
#define NPU2_CQ_SM_MISC_CFG1			0x008
#define NPU2_CQ_SM_MISC_CFG2			0x148
#define NPU2_PB_EPSILON				0x010
#define NPU2_TIMER_CFG				0x018
#define NPU2_GPU0_MEM_BAR			0x020
#define NPU2_GPU1_MEM_BAR			0x028
#define   NPU2_MEM_BAR_EN			PPC_BIT(0)
#define   NPU2_MEM_BAR_SEL_MEM			PPC_BITMASK(1,2)
#define   NPU2_MEM_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_MEM_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_MEM_BAR_NODE_ADDR		PPC_BITMASK(10,21)
#define   NPU2_MEM_BAR_ADDR			PPC_BITMASK(0,21)
#define   NPU2_MEM_BAR_POISON			PPC_BIT(22)
#define   NPU2_MEM_BAR_GRANULE			PPC_BIT(23)
#define   NPU2_MEM_BAR_BAR_SIZE			PPC_BITMASK(24,27)
#define   NPU2_MEM_BAR_MODE			PPC_BITMASK(28,31)
#define   NPU2_MEM_BAR_MASK			PPC_BITMASK(33,39)
#define NPU2_PHY_BAR				0x030
#define   NPU2_PHY_BAR_ENABLE			PPC_BIT(0)
#define   NPU2_PHY_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_PHY_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_PHY_BAR_NODE_ADDR		PPC_BITMASK(10,30)
#define   NPU2_PHY_BAR_ADDR			PPC_BITMASK(3,30)
#define NPU2_GENID_BAR				0x038
#define   NPU2_GENID_BAR_ENABLE			PPC_BIT(0)
#define   NPU2_GENID_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_GENID_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_GENID_BAR_NODE_ADDR		PPC_BITMASK(10,35)
#define   NPU2_GENID_BAR_ADDR			PPC_BITMASK(3,35)
#define   NPU2_GENID_BAR_POISON			PPC_BIT(39)
#define NPU2_LOW_WATER_MARKS			0x040
#define   NPU2_LOW_WATER_MARKS_ENABLE_MACHINE_ALLOC PPC_BIT(51)
#define NPU2_HIGH_WATER_MARKS			0x048
#define NPU2_RELAXED_ORDERING_CFG0		0x050
#define NPU2_RELAXED_ORDERING_CFG1		0x058
#define NPU2_RELAXED_ORDERING_CFG2		0x060
#define NPU2_NTL0_BAR				0x068
#define NPU2_NTL1_BAR				0x070
#define   NPU2_NTL_BAR_ENABLE			PPC_BIT(0)
#define   NPU2_NTL_BAR_GROUP			PPC_BITMASK(3,6)
#define   NPU2_NTL_BAR_CHIP			PPC_BITMASK(7,9)
#define   NPU2_NTL_BAR_NODE_ADDR		PPC_BITMASK(10,35)
#define   NPU2_NTL_BAR_ADDR			PPC_BITMASK(3,35)
#define   NPU2_NTL_BAR_POISON			PPC_BIT(36)
#define   NPU2_NTL_BAR_SIZE			PPC_BITMASK(39,43)
#define NPU2_PERF_CFG				0x078
#define NPU2_INHIBIT_CFG			0x080
#define NPU2_C_ERR_RPT_MSG0			0x088
#define NPU2_C_ERR_RPT_MSG1			0x090
#define NPU2_C_ERR_RPT_MSG2			0x098
#define NPU2_C_ERR_RPT_MSG3			0x0A0
#define NPU2_C_ERR_RPT_MSG4			0x0A8
#define NPU2_CQ_SM_STATUS			0x0B0
#define NPU2_C_ERR_RPT_FIRST0			0x0B8
#define NPU2_C_ERR_RPT_FIRST1			0x0C0
#define NPU2_C_ERR_RPT_FIRST2			0x0C8
#define NPU2_C_ERR_RPT_MASK0			0x0D0
#define NPU2_C_ERR_RPT_MASK1			0x0D8
#define NPU2_C_ERR_RPT_MASK2			0x0E0
#define NPU2_C_ERR_RPT_HOLD0			0x0E8
#define NPU2_C_ERR_RPT_HOLD1			0x0F0
#define NPU2_C_ERR_RPT_HOLD2			0x0F8
#define NPU2_PERF_ADDR_MATCH			0x100
#define NPU2_PERF_MATCH				0x108
#define NPU2_PERF_MASK				0x110
#define NPU2_DBG0_CFG				0x118
#define NPU2_DBG1_CFG				0x120

/* CTL block registers */
#define NPU2_CQ_CTL_MISC_CFG			0x000
#define   NPU2_CQ_CTL_MISC_CFG_CONFIG_OCAPI_MODE PPC_BIT(52)
#define   NPU2_CQ_CTL_MISC_CFG_CONFIG_OTL0_ENABLE PPC_BIT(55)
#define   NPU2_CQ_CTL_MISC_CFG_CONFIG_OTL1_ENABLE PPC_BIT(56)
#define NPU2_CQ_CTL_MISC_MMIOPA0_CONFIG		0x0B0
#define   NPU2_CQ_CTL_MISC_MMIOPA_ADDR		PPC_BITMASK(1,35)
#define   NPU2_CQ_CTL_MISC_MMIOPA_SIZE		PPC_BITMASK(39,43)
#define NPU2_CQ_CTL_MISC_MMIOPA1_CONFIG		0x0B8
#define NPU2_CQ_CTL_MISC_CFG1			0x008
#define NPU2_CQ_FUTURE_CFG2			0x010
#define NPU2_CQ_FUTURE_CFG3			0x018
#define NPU2_CQ_PERF_MATCH			0x020
#define NPU2_CQ_PERF_MASK			0x028
#define NPU2_CQ_CTL_PMU_CNT			0x030
#define NPU2_CQ_PERF_CFG			0x038
#define NPU2_CQ_DBG0_CFG			0x040
#define NPU2_CQ_DBG1_CFG			0x048
#define NPU2_CQ_BRICK0_BDF2PE_MAP0		0x050
#define NPU2_CQ_BRICK0_BDF2PE_MAP1		0x058
#define NPU2_CQ_BRICK0_BDF2PE_MAP2		0x060
#define NPU2_CQ_BRICK1_BDF2PE_MAP0		0x068
#define NPU2_CQ_BRICK1_BDF2PE_MAP1		0x070
#define NPU2_CQ_BRICK1_BDF2PE_MAP2		0x078
#define    NPU2_CQ_BRICK_BDF2PE_MAP_ENABLE	PPC_BIT(0)
#define    NPU2_CQ_BRICK_BDF2PE_MAP_WILDCARD	PPC_BIT(1)
#define    NPU2_CQ_BRICK_BDF2PE_MAP_PE		PPC_BITMASK(4,7)
#define    NPU2_CQ_BRICK_BDF2PE_MAP_BDF		PPC_BITMASK(8,23)
#define NPU2_CQ_LPC_THRESHOLD_CFG		0x080
#define NPU2_CQ_INHIBIT_CFG			0x088
#define NPU2_CQ_CTL_STATUS			0x090
#define   NPU2_CQ_CTL_STATUS_BRK0_AM_FENCED	PPC_BITMASK(48, 49)
#define   NPU2_CQ_CTL_STATUS_BRK1_AM_FENCED	PPC_BITMASK(50, 51)
#define NPU2_CQ_C_ERR_RPT_MSG0			0x0C0
#define NPU2_CQ_C_ERR_RPT_MSG1			0x0C8
#define NPU2_CQ_C_ERR_RPT_FIRST0		0x0D0
#define NPU2_CQ_C_ERR_RPT_FIRST1		0x0D8
#define NPU2_CQ_C_ERR_RPT_MASK0			0x0E0
#define NPU2_CQ_C_ERR_RPT_MASK1			0x0E8
#define NPU2_CQ_C_ERR_RPT_HOLD0			0x0F0
#define NPU2_CQ_C_ERR_RPT_HOLD1			0x0F8
#define NPU2_CQ_CTL_CONFIG_ADDR0		0x120
#define NPU2_CQ_CTL_CONFIG_ADDR1		0x128
#define   NPU2_CQ_CTL_CONFIG_ADDR_ENABLE	PPC_BIT(0)
#define   NPU2_CQ_CTL_CONFIG_ADDR_STATUS	PPC_BITMASK(1, 3)
#define   NPU2_CQ_CTL_CONFIG_ADDR_BUS_NUMBER	PPC_BITMASK(4, 11)
#define   NPU2_CQ_CTL_CONFIG_ADDR_DEVICE_NUMBER PPC_BITMASK(12, 16)
#define   NPU2_CQ_CTL_CONFIG_ADDR_FUNCTION_NUMBER PPC_BITMASK(17, 19)
#define   NPU2_CQ_CTL_CONFIG_ADDR_REGISTER_NUMBER PPC_BITMASK(20, 31)
#define   NPU2_CQ_CTL_CONFIG_ADDR_TYPE		PPC_BIT(32)
#define NPU2_CQ_CTL_FENCE_CONTROL_0		0x140
#define NPU2_CQ_CTL_FENCE_CONTROL_1		0x148
#define   NPU2_CQ_CTL_FENCE_CONTROL_REQUEST_FENCE PPC_BITMASK(0, 1)

/* DAT block registers */
#define NPU2_CQ_DAT_MISC_CFG			0x008
#define	  NPU2_CQ_DAT_MISC_CFG_CONFIG_OCAPI_MODE PPC_BIT(40)
#define NPU2_CQ_DAT_ECC_CFG			0x010
#define NPU2_CQ_DAT_SCRATCH0			0x018
#define NPU2_CQ_DAT_ECC_STATUS			0x020
#define NPU2_CQ_DAT_ECC_MASK			0x028
#define NPU2_CQ_DAT_ECC_FIRST			0x030
#define NPU2_CQ_DAT_PARITY			0x038
#define NPU2_CQ_DAT_PARITY_MASK			0x040
#define NPU2_CQ_DAT_PARITY_FIRST		0x048
#define NPU2_CQ_DAT_LOGIC			0x050
#define NPU2_CQ_DAT_LOGIC_MASK			0x058
#define NPU2_CQ_DAT_LOGIC_FIRST			0x060
#define NPU2_CQ_DAT_RAS_MSG0			0x068
#define NPU2_CQ_DAT_RAS_MSG1			0x070
#define NPU2_CQ_DAT_DBG0_CFG			0x080
#define NPU2_CQ_DAT_DBG1_CFG			0x088
#define NPU2_CQ_DAT_SCRATCH1			0x0E0
#define NPU2_CQ_DAT_BE_BUF_CTL			0x100
#define NPU2_CQ_DAT_BE_BUF_WORD0		0x108
#define NPU2_CQ_DAT_BE_BUF_WORD1		0x110
#define NPU2_CQ_DAT_BE_BUF_STATUS		0x118
#define NPU2_CQ_DAT_ERR_INJCT			0x130
#define NPU2_CQ_DAT_ERR_RPT_INJCT		0x138
#define NPU2_CQ_DAT_INHIBIT_CFG			0x140

/* NTL block registers */
#define NPU2_NTL_MISC_CFG2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x000)
#define   NPU2_NTL_MISC_CFG2_BRICK_ENABLE	PPC_BIT(0)
#define   NPU2_NTL_MISC_CFG2_NDL_RX_PARITY_ENA	PPC_BIT(16)
#define   NPU2_NTL_MISC_CFG2_NDL_TX_PARITY_ENA	PPC_BIT(17)
#define   NPU2_NTL_MISC_CFG2_NDL_PRI_PARITY_ENA	PPC_BIT(18)
#define   NPU2_NTL_MISC_CFG2_RCV_CREDIT_OVERFLOW_ENA PPC_BIT(19)
#define NPU2_NTL_MISC_CFG3(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x008)
#define NPU2_NTL_ERR_HOLD1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x010)
#define NPU2_NTL_ERR_MASK1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x018)
#define NPU2_NTL_ERR_FIRST1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x020)
#define NPU2_NTL_ERR_FIRST1_MASK(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x028)
#define NPU2_NTL_ERR_HOLD2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x030)
#define NPU2_NTL_ERR_MASK2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x038)
#define NPU2_NTL_ERR_FIRST2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x040)
#define NPU2_NTL_ERR_FIRST2_MASK(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x048)
#define NPU2_NTL_SCRATCH2(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x050)
#define NPU2_NTL_SCRATCH(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x058)
#define NPU2_NTL_DBG0(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x060)
#define NPU2_NTL_DBG1(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x068)
#define NPU2_NTL_PERF_CFG(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x070)
#define NPU2_NTL_PERF_CNT(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x078)
#define NPU2_NTL_CREQ_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x080)
#define NPU2_NTL_PRB_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x088)
#define NPU2_NTL_ATR_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x090)
#define NPU2_NTL_RSP_HDR(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x098)
#define NPU2_NTL_CRED_DATA(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x0A0)
#define NPU2_NTL_RSP_DATA(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x0A8)
#define NPU2_NTL_PRI_CFG(ndev)			NPU2_NTL_REG_OFFSET(ndev, 0x0B0)
#define NPU2_NTL_MISC_CFG1(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x0C0)
#define NPU2_NTL_SCRATCH1(ndev)			NPU2_NTLU_REG_OFFSET(ndev, 0x0D0)
#define NPU2_NTL_LOW_POWER_CFG(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x0E0)
#define NPU2_NTL_DBG_INHIBIT_CFG(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x220)
#define NPU2_NTL_DISPLAY_CTL(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x280)
#define NPU2_NTL_DISPLAY_DATA0(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x288)
#define NPU2_NTL_DISPLAY_DATA1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x290)
#define NPU2_NTL_DISPLAY_DATA2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x298)
#define NPU2_NTL_RAS_ERR_MSG0(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x300)
#define NPU2_NTL_RAS_ERR_MSG1(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x308)
#define NPU2_NTL_RAS_ERR_MSG2(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x310)
#define NPU2_NTL_RAS_ERR_MSG3(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x318)
#define NPU2_NTL_ECC_ERR_INJCT(ndev)		NPU2_NTL_REG_OFFSET(ndev, 0x340)
#define NPU2_NTL_CRED_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x400)
#define NPU2_NTL_PRB_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x410)
#define NPU2_NTL_ATR_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x418)
#define NPU2_NTL_RSP_HDR_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x428)
#define NPU2_NTL_CRED_DATA_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x430)
#define NPU2_NTL_RSP_DATA_CREDIT_TX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x438)
#define NPU2_NTL_CRED_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x440)
#define NPU2_NTL_DBD_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x448)
#define NPU2_NTL_ATSD_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x460)
#define NPU2_NTL_RSP_HDR_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x468)
#define NPU2_NTL_CRED_DATA_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x470)
#define NPU2_NTL_RSP_DATA_CREDIT_RX(ndev)	NPU2_NTLU_REG_OFFSET(ndev, 0x478)
#define NPU2_NTL_RB_CREDIT_RX(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x480)
#define NPU2_NTL_WAB_CREDIT_RX(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x488)
#define NPU2_NTL_CQ_FENCE_STATUS(ndev)		NPU2_NTLU_REG_OFFSET(ndev, 0x500)
#define NPU2_NTL_DL_CONTROL(ndev)		NPU2_DL_REG_OFFSET(ndev, 0xFFF4)
#define NPU2_NTL_DL_CONFIG(ndev)		NPU2_DL_REG_OFFSET(ndev, 0xFFF8)
#define NPU2_NTL_DL_CLK_CTRL(ndev)		NPU2_DL_REG_OFFSET(ndev, 0x001C)

/* OpenCAPI - XSL registers */
#define NPU2_XSL_PSL_LLCMD_A0			0x008
#define NPU2_XSL_PSL_SCNTL_A0			0x010
#define   NPU2_XSL_PSL_SCNTL_A0_MULTI_AFU_DIAL	PPC_BIT(0)
#define NPU2_XSL_DEF				0x040
#define NPU2_XSL_GP				0x058
#define   NPU2_XSL_GP_BLOOM_FILTER_ENABLE	PPC_BIT(16)
#define NPU2_XSL_WRAP_CFG			0x0C0
#define   NPU2_XSL_WRAP_CFG_XSLO_CLOCK_ENABLE	PPC_BIT(0)
#define NPU2_XSL_PSL_SPAP_A0			0
#define NPU2_XSL_PSL_SPAP_A1			0x18
#define   NPU2_XSL_PSL_SPAP_EN			PPC_BIT(63)

/* OpenCAPI - OTL registers */
#define NPU2_OTL_CONFIG0(stack, block)		NPU2_REG_OFFSET(stack, block, 0x000)
#define   NPU2_OTL_CONFIG0_EN			PPC_BIT(0)
#define   NPU2_OTL_CONFIG0_BLOCK_PE_HANDLE	PPC_BIT(1)
#define   NPU2_OTL_CONFIG0_BRICKID		PPC_BITMASK(2, 3)
#define   NPU2_OTL_CONFIG0_PE_MASK		PPC_BITMASK(4, 7)
#define   NPU2_OTL_CONFIG0_ERAT_HASH_0		PPC_BITMASK(8, 13)
#define   NPU2_OTL_CONFIG0_ERAT_HASH_1		PPC_BITMASK(14, 19)
#define   NPU2_OTL_CONFIG0_ERAT_HASH_2		PPC_BITMASK(20, 25)
#define   NPU2_OTL_CONFIG0_ERAT_HASH_3		PPC_BITMASK(26, 31)
#define   NPU2_OTL_CONFIG0_BLOCK_TID_OVERRIDE	PPC_BIT(50)
#define NPU2_OTL_TLX_CREDITS(stack, block)	NPU2_REG_OFFSET(stack, block, 0x050)
#define   NPU2_OTL_TLX_CREDITS_VC0_CREDITS	PPC_BITMASK(0, 7)
#define   NPU2_OTL_TLX_CREDITS_VC3_CREDITS	PPC_BITMASK(24, 31)
#define   NPU2_OTL_TLX_CREDITS_DCP0_CREDITS	PPC_BITMASK(32, 39)
#define   NPU2_OTL_TLX_CREDITS_DCP1_CREDITS	PPC_BITMASK(56, 63)
#define NPU2_OTL_VC_CREDITS(stack, block)	NPU2_REG_OFFSET(stack, block, 0x090)
#define NPU2_OTL_CONFIG1(stack, block)		NPU2_REG_OFFSET(stack, block, 0x058)
#define   NPU2_OTL_CONFIG1_TX_TEMP1_EN		PPC_BIT(1)
#define   NPU2_OTL_CONFIG1_TX_TEMP2_EN		PPC_BIT(2)
#define   NPU2_OTL_CONFIG1_TX_TEMP3_EN		PPC_BIT(3)
#define   NPU2_OTL_CONFIG1_TX_DRDY_WAIT		PPC_BITMASK(5, 7)
#define   NPU2_OTL_CONFIG1_TX_TEMP0_RATE	PPC_BITMASK(8, 11)
#define   NPU2_OTL_CONFIG1_TX_TEMP1_RATE	PPC_BITMASK(12, 15)
#define   NPU2_OTL_CONFIG1_TX_TEMP2_RATE	PPC_BITMASK(16, 19)
#define   NPU2_OTL_CONFIG1_TX_TEMP3_RATE	PPC_BITMASK(20, 23)
#define   NPU2_OTL_CONFIG1_TX_CRET_FREQ 	PPC_BITMASK(32, 34)
#define   NPU2_OTL_CONFIG1_TX_AGE_FREQ		PPC_BITMASK(35, 39)
#define   NPU2_OTL_CONFIG1_TX_RS2_HPWAIT	PPC_BITMASK(40, 45)
#define   NPU2_OTL_CONFIG1_TX_RQ4_HPWAIT	PPC_BITMASK(46, 51)
#define   NPU2_OTL_CONFIG1_TX_RQ6_HPWAIT	PPC_BITMASK(52, 57)
#define   NPU2_OTL_CONFIG1_TX_CBUF_ECC_DIS	PPC_BIT(58)
#define   NPU2_OTL_CONFIG1_TX_STOP_LINK		PPC_BIT(59)
#define   NPU2_OTL_CONFIG1_TX_STOP_ON_UE	PPC_BIT(60)
#define   NPU2_OTL_CONFIG1_TX_T0_MASK_CRTN0	PPC_BIT(61)
#define   NPU2_OTL_CONFIG1_TX_T123_MASK_CRTN0	PPC_BIT(62)
#define NPU2_OTL_CONFIG2(stack, block)		NPU2_REG_OFFSET(stack, block, 0x0C0)
#define   NPU2_OTL_CONFIG2_TX_SEND_EN		PPC_BIT(0)

#define NPU2_OTL_OSL_DSISR(stack, block)	NPU2_REG_OFFSET(stack, block, 0x000)
#define NPU2_OTL_OSL_DAR(stack, block)		NPU2_REG_OFFSET(stack, block, 0x008)
#define NPU2_OTL_OSL_TFC(stack, block)		NPU2_REG_OFFSET(stack, block, 0x010)
#define NPU2_OTL_OSL_PEHANDLE(stack, block)	NPU2_REG_OFFSET(stack, block, 0x018)

/* Misc block registers. Unlike the SM/CTL/DAT/NTL registers above
 * there is only a single instance of each of these in the NPU so we
 * define them as absolute offsets. */
#define NPU2_MISC_DBG_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x000)
#define NPU2_MISC_RELAXTED_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x008)
#define NPU2_MISC_LCO_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x010)
#define NPU2_MISC_OPTICAL_IO_CFG0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x018)
#define   NPU2_MISC_OPTICAL_IO_CFG0_NDLMUX_BRK0TO2 PPC_BITMASK(0, 2)
#define   NPU2_MISC_OPTICAL_IO_CFG0_OCMUX_BRK0TO1 PPC_BITMASK(3, 4)
#define   NPU2_MISC_OPTICAL_IO_CFG0_OCMUX_BRK4TO5 PPC_BITMASK(5, 6)
#define NPU2_MISC_ERR_RPT_HOLD			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x020)
#define NPU2_MISC_ERR_RPT_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x028)
#define NPU2_MISC_CFG				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x030)
#define   NPU2_MISC_CFG_CONFIG_SYNC_WAIT	PPC_BITMASK(0,4)
#define   NPU2_MISC_CFG_PERF_CONFIG_ENABLE	PPC_BIT(5)
#define   NPU2_MISC_CFG_PERF_CONFIG_PE_MASK	PPC_BIT(6)
#define   NPU2_MISC_CFG_PERF_CONFIG_PE_MATCH	PPC_BITMASK(7,10)
#define   NPU2_MISC_CFG_IPI_PS			PPC_BIT(11)
#define   NPU2_MISC_CFG_IPI_PS_4K		0
#define   NPU2_MISC_CFG_IPI_PS_64K		1
#define   NPU2_MISC_CFG_IPI_OS			PPC_BIT(12)
#define   NPU2_MISC_CFG_IPI_OS_AIX		0
#define   NPU2_MISC_CFG_IPI_OS_LINUX		1
#define NPU2_MISC_INHIBIT_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x038)
#define NPU2_MISC_FREEZE_ENABLE0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x040)
#define NPU2_MISC_FREEZE_ENABLE1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x048)
#define NPU2_MISC_FENCE_ENABLE0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x050)
#define NPU2_MISC_FENCE_ENABLE1			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x058)
#define NPU2_MISC_IRQ_ENABLE0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x060)
#define NPU2_MISC_IRQ_ENABLE1			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x068)
#define NPU2_MISC_NPU_VERSION			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x080)
#define NPU2_MISC_ERR_CTL_CFG			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x088)
#define NPU2_MISC_RING_ACK_ERR			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x090)
#define NPU2_MISC_IRQ_BASE			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x098)
#define   NPU2_MISC_IRQ_BASE_MASK		PPC_BITMASK(13, 51)
#define NPU2_MISC_ERR_BRICK_GROUP		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0A0)
#define NPU2_MISC_FREEZE_STATE			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0A8)
#define NPU2_MISC_FENCE_STATE			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0B0)
#define NPU2_MISC_IRQ_REQUEST			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x0B8)
#define NPU2_MISC_BRICK0_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x100)
#define NPU2_MISC_BRICK0_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x108)
#define NPU2_MISC_BRICK0_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x110)
#define NPU2_MISC_BRICK1_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x118)
#define NPU2_MISC_BRICK1_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x120)
#define NPU2_MISC_BRICK1_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x128)
#define NPU2_MISC_BRICK2_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x130)
#define NPU2_MISC_BRICK2_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x138)
#define NPU2_MISC_BRICK2_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x140)
#define NPU2_MISC_BRICK3_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x148)
#define NPU2_MISC_BRICK3_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x150)
#define NPU2_MISC_BRICK3_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x158)
#define NPU2_MISC_BRICK4_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x160)
#define NPU2_MISC_BRICK4_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x168)
#define NPU2_MISC_BRICK4_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x170)
#define NPU2_MISC_BRICK5_BDF2PE_MAP0		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x178)
#define NPU2_MISC_BRICK5_BDF2PE_MAP1		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x180)
#define NPU2_MISC_BRICK5_BDF2PE_MAP2		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x188)
#define   NPU2_MISC_BRICK_BDF2PE_MAP_ENABLE	PPC_BIT(0)
#define   NPU2_MISC_BRICK_BDF2PE_MAP_PE		PPC_BITMASK(4,7)
#define   NPU2_MISC_BRICK_BDF2PE_MAP_BDF	PPC_BITMASK(8,23)
#define NPU2_MISC_PESTB(pe)			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x200 + (pe)*8)
#define NPU2_MISC_IRQ_LOG0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x300)
#define NPU2_MISC_IRQ_LOG01			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x308)
#define NPU2_MISC_IRQ_LOG02			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x310)
#define NPU2_MISC_IRQ_LOG03			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x318)
#define NPU2_MISC_IRQ_LOG04			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x320)
#define NPU2_MISC_IRQ_LOG05			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x328)
#define NPU2_MISC_IRQ_LOG06			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x330)
#define NPU2_MISC_IRQ_LOG07			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x338)
#define NPU2_MISC_IRQ_LOG08			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x340)
#define NPU2_MISC_IRQ_LOG09			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x348)
#define NPU2_MISC_IRQ_LOG10			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x350)
#define NPU2_MISC_IRQ_LOG11			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x358)
#define NPU2_MISC_IRQ_LOG12			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x360)
#define NPU2_MISC_IRQ_LOG13			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x368)
#define NPU2_MISC_IRQ_LOG14			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x370)
#define NPU2_MISC_IRQ_LOG15			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x378)
#define NPU2_MISC_IRQ_ENABLE2			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_MISC, 0x408)

/* Misc register, direct access only */
#define NPU2_MISC_FIR_MASK1		0x2C43

/* ATS block registers */
#define NPU2_ATS_PMU_CTL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x000)
#define NPU2_ATS_PMU_CNT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x008)
#define NPU2_ATS_ERR_INJCT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x010)
#define NPU2_ATS_DBG_CTL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x018)
#define NPU2_ATS_CHICKEN_SWITCH			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x020)
#define NPU2_ATS_ERR_RPT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x028)
#define NPU2_ATS_ERR_RPT_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x030)
#define NPU2_ATS_CTL				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x100)
#define NPU2_ATS_IODA_TBL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x108)
#define   NPU2_ATS_IODA_TBL_TVT			9
#define      NPU2_ATS_IODA_TBL_TVT_TTA		PPC_BITMASK(0,47)
#define      NPU2_ATS_IODA_TBL_TVT_LEVEL	PPC_BITMASK(48,50)
#define      NPU2_ATS_IODA_TBL_TVT_SIZE		PPC_BITMASK(51,55)
#define      NPU2_ATS_IODA_TBL_TVT_PSIZE	PPC_BITMASK(59,63)
#define   NPU2_ATS_IODA_TBL_TCD			10
#define   NPU2_ATS_IODA_TBL_TDR			11
#define   NPU2_ATS_IODA_TBL_TDRMEM		12
#define   NPU2_ATS_IODA_TBL_XLTEA		16
#define   NPU2_ATS_IODA_TBL_AUTOINC		PPC_BIT(0)
#define   NPU2_ATS_IODA_TBL_SELECT		PPC_BITMASK(11,15)
#define   NPU2_ATS_IODA_TBL_INDEX		PPC_BITMASK(54,63)
#define NPU2_ATS_IODA_DATA			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x110)
#define NPU2_ATS_DMA_SYNC			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x118)
#define NPU2_ATS_TCE_KILL			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x120)
#define   NPU2_ATS_TCE_KILL_ALL			PPC_BIT(0)
#define   NPU2_ATS_TCE_KILL_ONE			PPC_BIT(2)
#define   NPU2_ATS_TCE_KILL_PENUM		PPC_BITMASK(4, 7)
#define NPU2_ATS_QUIESCE_DMA			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x128)
#define NPU2_ATS_TCE_TIMEOUT_CTL		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x130)
#define NPU2_ATS_ERR_STATUS			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x138)
#define NPU2_ATS_ERR_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x140)
#define NPU2_ATS_ERR_FIRST			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x148)
#define NPU2_ATS_ERR_FIRST_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_ATS, 0x150)

/* XTS block registers */
#define NPU2_XTS_ERR_RPT_STATUS			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x000)
#define NPU2_XTS_ERR_RPT_INJCT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x008)
#define NPU2_XTS_ERR_MASK			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x010)
#define NPU2_XTS_ERR_FIRST			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x018)
#define NPU2_XTS_CFG				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x020)
#define   NPU2_XTS_CFG_MMIOSD			PPC_BIT(1)
#define   NPU2_XTS_CFG_TRY_ATR_RO		PPC_BIT(6)
#define   NPU2_XTS_CFG_OPENCAPI			PPC_BIT(15)
#define NPU2_XTS_CFG2				NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x028)
#define   NPU2_XTS_CFG2_NO_FLUSH_ENA		PPC_BIT(49)
#define   NPU2_XTS_CFG2_XSL1_ENA		PPC_BIT(54)
#define   NPU2_XTS_CFG2_XSL2_ENA		PPC_BIT(55)
#define NPU2_XTS_DBG_CFG0			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x030)
#define NPU2_XTS_DBG_CFG1			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x038)
#define NPU2_XTS_PMU_CNT			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x040)
#define NPU2_XTS_ATR_MISS			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x050)
#define NPU2_XTS_ATR_MISS_CLR			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x058)
#define NPU2_XTS_ATR_MISS2			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x060)
#define NPU2_XTS_MMIO_ATSD0_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x100)
#define NPU2_XTS_MMIO_ATSD1_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x108)
#define NPU2_XTS_MMIO_ATSD2_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x110)
#define NPU2_XTS_MMIO_ATSD3_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x118)
#define NPU2_XTS_MMIO_ATSD4_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x120)
#define NPU2_XTS_MMIO_ATSD5_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x128)
#define NPU2_XTS_MMIO_ATSD6_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x130)
#define NPU2_XTS_MMIO_ATSD7_LPARID		NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x138)
#define NPU2_XTS_BDF_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x4000)
#define   NPU2_XTS_BDF_MAP_VALID		PPC_BIT(0)
#define   NPU2_XTS_BDF_MAP_UNFILT		PPC_BIT(1)
#define   NPU2_XTS_BDF_MAP_STACK		PPC_BITMASK(4, 6)
#define   NPU2_XTS_BDF_MAP_BRICK		PPC_BIT(7)
#define   NPU2_XTS_BDF_MAP_BDF			PPC_BITMASK(16, 31)
#define   NPU2_XTS_BDF_MAP_XLAT			PPC_BITMASK(39, 40)
#define   NPU2_XTS_BDF_MAP_LPCR_ISL		PPC_BIT(44)
#define   NPU2_XTS_BDF_MAP_LPCR_TC		PPC_BIT(45)
#define   NPU2_XTS_BDF_MAP_LPARSHORT		PPC_BITMASK(48, 51)
#define   NPU2_XTS_BDF_MAP_LPARID		PPC_BITMASK(52, 63)
#define NPU2_XTS_PID_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x8000)
#define   NPU2_XTS_PID_MAP_VALID_ATRGPA0	PPC_BIT(0)
#define   NPU2_XTS_PID_MAP_VALID_ATRGPA1	PPC_BIT(1)
#define   NPU2_XTS_PID_MAP_VALID_ATSD		PPC_BIT(2)
#define   NPU2_XTS_PID_MAP_MSR			PPC_BITMASK(25,31)
#define   NPU2_XTS_PID_MAP_MSR_DR		PPC_BIT(25)
#define   NPU2_XTS_PID_MAP_MSR_TA		PPC_BIT(26)
#define   NPU2_XTS_PID_MAP_MSR_HV		PPC_BIT(27)
#define   NPU2_XTS_PID_MAP_MSR_PR		PPC_BIT(28)
#define   NPU2_XTS_PID_MAP_MSR_US		PPC_BIT(29)
#define   NPU2_XTS_PID_MAP_MSR_SF		PPC_BIT(30)
#define   NPU2_XTS_PID_MAP_MSR_UV		PPC_BIT(31)
#define   NPU2_XTS_PID_MAP_LPARSHORT		PPC_BITMASK(40, 43)
#define   NPU2_XTS_PID_MAP_PASID       		PPC_BITMASK(44, 63)
#define NPU2_XTS_SEIDR_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x8008)
#define NPU2_XTS_AMR_MAP			NPU2_REG_OFFSET(NPU2_STACK_MISC, NPU2_BLOCK_XTS, 0x8010)

/* XTS ATSD block */
#define NPU2_XTS_MMIO_ATSD_LAUNCH		0x000
#define NPU2_XTS_MMIO_ATSD_AVA			0x008
#define NPU2_XTS_MMIO_ATSD_STATUS		0x010

/* ALTD SCOM addresses */
#define NPU2_MISC_SCOM_IND_SCOM_ADDR		0x68e
#define  NPU2_MISC_DA_ADDR			PPC_BITMASK(0, 23)
#define  NPU2_MISC_DA_LEN			PPC_BITMASK(24, 25)
#define   NPU2_MISC_DA_LEN_4B			2
#define   NPU2_MISC_DA_LEN_8B			3
#define NPU2_MISC_SCOM_IND_SCOM_DATA		0x68f

#define NPU2_FIR_OFFSET				0x40
#define NPU2_FIR_MASK_OFFSET			0x3
#define NPU2_FIR_ACTION0_OFFSET			0x6
#define NPU2_FIR_ACTION1_OFFSET			0x7

#define NPU2_FIR_REGISTER_0			0x0000000005013C00
#define NPU2_FIR_REGISTER_1			0x0000000005013C40
#define NPU2_FIR_REGISTER_2			0x0000000005013C80

#define NPU2_TOTAL_FIR_REGISTERS		3

/*
 * Can't use enums for 64 bit values, use #defines
 */
#define NPU2_CHECKSTOP_REG0_NTL_ARRAY_CE		PPC_BIT(0)
#define NPU2_CHECKSTOP_REG0_NTL_ARRAY_HDR_CE		PPC_BIT(1)
#define NPU2_CHECKSTOP_REG0_NTL_ARRAY_DATA_UE		PPC_BIT(2)
#define NPU2_CHECKSTOP_REG0_NTL_NVL_FLIT_PERR		PPC_BIT(3)
#define NPU2_CHECKSTOP_REG0_NTL_NVL_DATA_PERR		PPC_BIT(4)
#define NPU2_CHECKSTOP_REG0_NTL_NVL_PKT_MALFOR		PPC_BIT(5)
#define NPU2_CHECKSTOP_REG0_NTL_NVL_PKT_UNSUPPORTED	PPC_BIT(6)
#define NPU2_CHECKSTOP_REG0_NTL_NVL_CONFIG_ERR		PPC_BIT(7)
#define NPU2_CHECKSTOP_REG0_NTL_NVL_CRC_ERR		PPC_BIT(8)
#define NPU2_CHECKSTOP_REG0_NTL_PRI_ERR			PPC_BIT(9)
#define NPU2_CHECKSTOP_REG0_NTL_LOGIC_ERR		PPC_BIT(10)
#define NPU2_CHECKSTOP_REG0_NTL_LMD_POISON		PPC_BIT(11)
#define NPU2_CHECKSTOP_REG0_NTL_ARRAY_DATA_SUE		PPC_BIT(12)
#define NPU2_CHECKSTOP_REG0_CTL_ARRAY_CE		PPC_BIT(13)
#define NPU2_CHECKSTOP_REG0_CTL_PBUS_RECOV_ERR		PPC_BIT(14)
#define NPU2_CHECKSTOP_REG0_CTL_REG_RING_ERR		PPC_BIT(15)
#define NPU2_CHECKSTOP_REG0_CTL_MMIO_ST_DATA_UE		PPC_BIT(16)
#define NPU2_CHECKSTOP_REG0_CTL_PEF			PPC_BIT(17)
#define NPU2_CHECKSTOP_REG0_CTL_NVL_CFG_ERR		PPC_BIT(18)
#define NPU2_CHECKSTOP_REG0_CTL_NVL_FATAL_ERR		PPC_BIT(19)
#define NPU2_CHECKSTOP_REG0_RESERVED_1			PPC_BIT(20)
#define NPU2_CHECKSTOP_REG0_CTL_ARRAY_UE		PPC_BIT(21)
#define NPU2_CHECKSTOP_REG0_CTL_PBUS_PERR		PPC_BIT(22)
#define NPU2_CHECKSTOP_REG0_CTL_PBUS_FATAL_ERR		PPC_BIT(23)
#define NPU2_CHECKSTOP_REG0_CTL_PBUS_CONFIG_ERR		PPC_BIT(24)
#define NPU2_CHECKSTOP_REG0_CTL_FWD_PROGRESS_ERR	PPC_BIT(25)
#define NPU2_CHECKSTOP_REG0_CTL_LOGIC_ERR		PPC_BIT(26)
#define NPU2_CHECKSTOP_REG0_DAT_DATA_BE_UE		PPC_BIT(29)
#define NPU2_CHECKSTOP_REG0_DAT_DATA_BE_CE		PPC_BIT(30)
#define NPU2_CHECKSTOP_REG0_DAT_DATA_BE_PERR		PPC_BIT(31)
#define NPU2_CHECKSTOP_REG0_DAT_CREG_PERR		PPC_BIT(32)
#define NPU2_CHECKSTOP_REG0_DAT_RTAG_PERR		PPC_BIT(33)
#define NPU2_CHECKSTOP_REG0_DAT_STATE_PERR		PPC_BIT(34)
#define NPU2_CHECKSTOP_REG0_DAT_LOGIC_ERR		PPC_BIT(35)
#define NPU2_CHECKSTOP_REG0_DAT_DATA_BE_SUE		PPC_BIT(36)
#define NPU2_CHECKSTOP_REG0_DAT_PBRX_SUE		PPC_BIT(37)
#define NPU2_CHECKSTOP_REG0_XTS_INT			PPC_BIT(40)
#define NPU2_CHECKSTOP_REG0_XTS_SRAM_CE			PPC_BIT(41)
#define NPU2_CHECKSTOP_REG0_XTS_SRAM_UE			PPC_BIT(42)
#define NPU2_CHECKSTOP_REG0_XTS_PROTOCOL_CE		PPC_BIT(43)
#define NPU2_CHECKSTOP_REG0_XTS_PROTOCOL_UE		PPC_BIT(44)
#define NPU2_CHECKSTOP_REG0_XTS_PBUS_PROTOCOL		PPC_BIT(45)

#define NPU2_CHECKSTOP_REG1_NDL_BRK0_STALL			PPC_BIT(0)
#define NPU2_CHECKSTOP_REG1_NDL_BRK0_NOSTALL			PPC_BIT(1)
#define NPU2_CHECKSTOP_REG1_NDL_BRK1_STALL			PPC_BIT(2)
#define NPU2_CHECKSTOP_REG1_NDL_BRK1_NOSTALL			PPC_BIT(3)
#define NPU2_CHECKSTOP_REG1_NDL_BRK2_STALL			PPC_BIT(4)
#define NPU2_CHECKSTOP_REG1_NDL_BRK2_NOSTALL			PPC_BIT(5)
#define NPU2_CHECKSTOP_REG1_NDL_BRK3_STALL			PPC_BIT(6)
#define NPU2_CHECKSTOP_REG1_NDL_BRK3_NOSTALL			PPC_BIT(7)
#define NPU2_CHECKSTOP_REG1_NDL_BRK4_STALL			PPC_BIT(8)
#define NPU2_CHECKSTOP_REG1_NDL_BRK4_NOSTALL			PPC_BIT(9)
#define NPU2_CHECKSTOP_REG1_NDL_BRK5_STALL			PPC_BIT(10)
#define NPU2_CHECKSTOP_REG1_NDL_BRK5_NOSTALL			PPC_BIT(11)
#define NPU2_CHECKSTOP_REG1_MISC_REG_RING_ERR			PPC_BIT(12)
#define NPU2_CHECKSTOP_REG1_MISC_INT_RA_PERR			PPC_BIT(13)
#define NPU2_CHECKSTOP_REG1_MISC_DA_ADDR_PERR			PPC_BIT(14)
#define NPU2_CHECKSTOP_REG1_MISC_CTRL_PERR			PPC_BIT(15)
#define NPU2_CHECKSTOP_REG1_MISC_NMMU_ERR			PPC_BIT(16)
#define NPU2_CHECKSTOP_REG1_ATS_TVT_ENTRY_INVALID		PPC_BIT(17)
#define NPU2_CHECKSTOP_REG1_ATS_TVT_ADDR_RANGE_ERR		PPC_BIT(18)
#define NPU2_CHECKSTOP_REG1_ATS_TCE_PAGE_ACCESS_CA_ERR		PPC_BIT(19)
#define NPU2_CHECKSTOP_REG1_ATS_TCE_CACHE_MULT_HIT_ERR		PPC_BIT(20)
#define NPU2_CHECKSTOP_REG1_ATS_TCE_PAGE_ACCESS_TW_ERR		PPC_BIT(21)
#define NPU2_CHECKSTOP_REG1_ATS_TCE_REQ_TO_ERR			PPC_BIT(22)
#define NPU2_CHECKSTOP_REG1_ATS_TCD_PERR			PPC_BIT(23)
#define NPU2_CHECKSTOP_REG1_ATS_TDR_PERR			PPC_BIT(24)
#define NPU2_CHECKSTOP_REG1_ATS_AT_EA_UE			PPC_BIT(25)
#define NPU2_CHECKSTOP_REG1_ATS_AT_EA_CE			PPC_BIT(26)
#define NPU2_CHECKSTOP_REG1_ATS_AT_TDRMEM_UE			PPC_BIT(27)
#define NPU2_CHECKSTOP_REG1_ATS_AT_TDRMEM_CE			PPC_BIT(28)
#define NPU2_CHECKSTOP_REG1_ATS_AT_RSPOUT_UE			PPC_BIT(29)
#define NPU2_CHECKSTOP_REG1_ATS_AT_RSPOUT_CE			PPC_BIT(30)
#define NPU2_CHECKSTOP_REG1_ATS_TVT_PERR			PPC_BIT(31)
#define NPU2_CHECKSTOP_REG1_ATS_IODA_ADDR_PERR			PPC_BIT(32)
#define NPU2_CHECKSTOP_REG1_ATS_NPU_CTRL_PERR			PPC_BIT(33)
#define NPU2_CHECKSTOP_REG1_ATS_NPU_TOR_PERR			PPC_BIT(34)
#define NPU2_CHECKSTOP_REG1_ATS_INVAL_IODA_TBL_SEL		PPC_BIT(35)

#define NPU2_CHECKSTOP_REG2_XSL_MMIO_INVALIDATE_REQ_WHILE_1_INPROG	PPC_BIT(36)
#define NPU2_CHECKSTOP_REG2_XSL_UNEXPECTED_ITAG_PORT_0			PPC_BIT(37)
#define NPU2_CHECKSTOP_REG2_XSL_UNEXPECTED_ITAG_PORT_1			PPC_BIT(38)
#define NPU2_CHECKSTOP_REG2_XSL_UNEXPECTED_RD_PEE_COMPLETION		PPC_BIT(39)
#define NPU2_CHECKSTOP_REG2_XSL_UNEXPECTED_CO_RESP			PPC_BIT(40)
#define NPU2_CHECKSTOP_REG2_XSL_XLAT_REQ_WHILE_SPAP_INVALID		PPC_BIT(41)
#define NPU2_CHECKSTOP_REG2_XSL_INVALID_PEE				PPC_BIT(42)
#define NPU2_CHECKSTOP_REG2_XSL_BLOOM_FILTER_PROTECT_ERR		PPC_BIT(43)
#define NPU2_CHECKSTOP_REG2_XSL_CE					PPC_BIT(46)
#define NPU2_CHECKSTOP_REG2_XSL_UE					PPC_BIT(47)
#define NPU2_CHECKSTOP_REG2_XSL_SLBI_TLBI_BUFF_OVERFLOW			PPC_BIT(48)
#define NPU2_CHECKSTOP_REG2_XSL_SBE_CORR_ERR_PB_CHKOUT_RSP_DATA		PPC_BIT(49)
#define NPU2_CHECKSTOP_REG2_XSL_UE_PB_CHKOUT_RSP_DATA			PPC_BIT(50)
#define NPU2_CHECKSTOP_REG2_XSL_SUE_PB_CHKOUT_RSP_DATA			PPC_BIT(51)

/* OpenCAPI - PowerBus and OBus configuration SCOM addresses */
#define PU_IOE_PB_MISC_CFG			0x5013823
#define   PU_IOE_PB_MISC_CFG_SEL_03_NPU_NOT_PB	PPC_BIT(13)
#define   PU_IOE_PB_MISC_CFG_SEL_04_NPU_NOT_PB	PPC_BIT(14)
#define   PU_IOE_PB_MISC_CFG_SEL_05_NPU_NOT_PB	PPC_BIT(15)
#define OBUS_LL0_IOOL_PHY_CONFIG		0x901080C
#define OBUS_LL3_IOOL_PHY_CONFIG		0xC01080C
#define   OBUS_IOOL_PHY_CONFIG_ODL0_ENABLED	PPC_BIT(52)
#define   OBUS_IOOL_PHY_CONFIG_ODL1_ENABLED	PPC_BIT(53)
#define   OBUS_IOOL_PHY_CONFIG_ODL_PHY_SWAP	PPC_BIT(54)
#define   OBUS_IOOL_PHY_CONFIG_LINK0_OLL_ENABLED PPC_BIT(58)
#define   OBUS_IOOL_PHY_CONFIG_LINK1_OLL_ENABLED PPC_BIT(59)
#define   OBUS_IOOL_PHY_CONFIG_NV0_NPU_ENABLED	PPC_BIT(61)
#define   OBUS_IOOL_PHY_CONFIG_NV1_NPU_ENABLED	PPC_BIT(62)
#define   OBUS_IOOL_PHY_CONFIG_NV2_NPU_ENABLED	PPC_BIT(63)
#define PU_IOE_PB_FP01_CFG			0x501380A
#define PU_IOE_PB_FP23_CFG			0x501380B
#define PU_IOE_PB_FP45_CFG			0x501380C
#define PU_IOE_PB_FP67_CFG			0x501380D
#define    PU_IOE_PB_FP_CFG_FP0_FMR_DISABLE	PPC_BIT(20)
#define    PU_IOE_PB_FP_CFG_FP0_PRS_DISABLE	PPC_BIT(25)
#define    PU_IOE_PB_FP_CFG_FP1_FMR_DISABLE	PPC_BIT(52)
#define    PU_IOE_PB_FP_CFG_FP1_PRS_DISABLE	PPC_BIT(57)

#define OB0_ODL0_CONFIG				0x901082A
#define OB0_ODL1_CONFIG				0x901082B
#define OB3_ODL0_CONFIG				0xC01082A
#define OB3_ODL1_CONFIG				0xC01082B
#define   OB_ODL_CONFIG_RESET			PPC_BIT(0)
#define   OB_ODL_CONFIG_VERSION			PPC_BITMASK(2, 7)
#define   OB_ODL_CONFIG_TRAIN_MODE		PPC_BITMASK(8, 11)
#define   OB_ODL_CONFIG_SUPPORTED_MODES		PPC_BITMASK(12, 15)
#define   OB_ODL_CONFIG_X4_BACKOFF_ENABLE	PPC_BIT(16)
#define   OB_ODL_CONFIG_PHY_CNTR_LIMIT		PPC_BITMASK(20, 23)
#define   OB_ODL_CONFIG_DEBUG_ENABLE		PPC_BIT(33)
#define   OB_ODL_CONFIG_FWD_PROGRESS_TIMER	PPC_BITMASK(40, 43)

#define OB0_ODL0_STATUS				0x901082C
#define OB0_ODL1_STATUS				0x901082D
#define OB3_ODL0_STATUS				0xC01082C
#define OB3_ODL1_STATUS				0xC01082D
#define   OB_ODL_STATUS_TRAINED_MODE		PPC_BITMASK(0,3)
#define   OB_ODL_STATUS_TRAINING_STATE_MACHINE	PPC_BITMASK(49, 51)

#define OB0_ODL0_TRAINING_STATUS		0x901082E
#define OB0_ODL1_TRAINING_STATUS		0x901082F
#define OB3_ODL0_TRAINING_STATUS		0xC01082E
#define OB3_ODL1_TRAINING_STATUS		0xC01082F
#define   OB_ODL_TRAINING_STATUS_STS_RX_PATTERN_B PPC_BITMASK(8, 15)

#endif /* __NPU2_REGS_H */
