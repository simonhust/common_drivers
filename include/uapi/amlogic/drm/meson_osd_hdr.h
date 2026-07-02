/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Unified OSD HDR LUT interface for subtitle HDR mapping.
 * Works across G12, T7, S5, S6, S7D, T3X SoCs.
 *
 * Copyright (c) 2024 Amlogic, Inc. All rights reserved.
 */
#ifndef _MESON_OSD_HDR_H_
#define _MESON_OSD_HDR_H_

#include <linux/types.h>
#include <linux/bits.h>

/*
 * LUT sizes from hdr2_ext.h
 */
#define MESON_HDR_EOTF_LUT_SIZE  143
#define MESON_HDR_OOTF_LUT_SIZE  149
#define MESON_HDR_OETF_LUT_SIZE  149

/*
 * LUT type flags - bitmask for which LUTs to update
 */
#define MESON_HDR_LUT_EOTF  BIT(0)
#define MESON_HDR_LUT_OOTF  BIT(1)
#define MESON_HDR_LUT_OETF  BIT(2)
#define MESON_HDR_LUT_ALL   (MESON_HDR_LUT_EOTF | MESON_HDR_LUT_OOTF | MESON_HDR_LUT_OETF)

/*
 * HDR transfer function type
 */
#define MESON_HDR_TF_SDR   0  /* Disable LUT, passthrough */
#define MESON_HDR_TF_PQ    1  /* SMPTE ST 2084 (HDR10, DV, HDR10+, Vivid) */
#define MESON_HDR_TF_HLG   2  /* ARIB STD-B67 */

/*
 * OSD HDR LUT ioctl structure.
 *
 * Userspace fills in the desired LUT data and calls the ioctl.
 * Kernel handles SoC-specific register addresses internally.
 *
 * For T7/S5: use osd_index=2 (OSD3) since OSD2 has no HDR2.
 * For G12/S6/S7D/T3X: use osd_index=1 (OSD2).
 * For T3: not supported (no LUT hardware).
 */
struct drm_meson_osd_hdr_lut {
	/** @osd_index: OSD plane index (0=OSD1, 1=OSD2, 2=OSD3) */
	__u32 osd_index;
	/** @tf_type: Transfer function type (MESON_HDR_TF_*) */
	__u32 tf_type;
	/** @lut_flags: Bitmask of LUTs to update (MESON_HDR_LUT_*) */
	__u32 lut_flags;
	/** @reserved: Must be zero */
	__u32 reserved;
	/** @eotf_lut_ptr: Userspace pointer to __u32[MESON_HDR_EOTF_LUT_SIZE] */
	__u64 eotf_lut_ptr;
	/** @ootf_lut_ptr: Userspace pointer to __u32[MESON_HDR_OOTF_LUT_SIZE] */
	__u64 ootf_lut_ptr;
	/** @oetf_lut_ptr: Userspace pointer to __u32[MESON_HDR_OETF_LUT_SIZE] */
	__u64 oetf_lut_ptr;
};

#endif /* _MESON_OSD_HDR_H_ */
