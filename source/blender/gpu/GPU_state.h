/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/** \file
 * \ingroup gpu
 */

#pragma once

#include "BLI_utildefines.h"

typedef enum eGPUWriteMask {
  GPU_WRITE_NONE = 0,
  GPU_WRITE_RED = (1 << 0),
  GPU_WRITE_GREEN = (1 << 1),
  GPU_WRITE_BLUE = (1 << 2),
  GPU_WRITE_ALPHA = (1 << 3),
  GPU_WRITE_DEPTH = (1 << 4),
  GPU_WRITE_COLOR = (GPU_WRITE_RED | GPU_WRITE_GREEN | GPU_WRITE_BLUE | GPU_WRITE_ALPHA),
} eGPUWriteMask;

//ENUM_OPERATORS(eGPUWriteMask) // Game engine transition WARNING I commented to fix a compil error but idk what it can do

/**
 * Defines the fixed pipeline blending equation.
 * SRC is the output color from the shader.
 * DST is the color from the framebuffer.
 * The blending equation is :
 *  (SRC * A) + (DST * B).
 * The blend mode will modify the A and B parameters.
 */
typedef enum eGPUBlend {
  GPU_BLEND_NONE = 0,
  /** Premult variants will _NOT_ multiply rgb output by alpha. */
  GPU_BLEND_ALPHA,
  GPU_BLEND_ALPHA_PREMULT,
  GPU_BLEND_ADDITIVE,
  GPU_BLEND_ADDITIVE_PREMULT,
  GPU_BLEND_MULTIPLY,
  GPU_BLEND_SUBTRACT,
  /** Replace logic op: SRC * (1 - DST)
   * NOTE: Does not modify alpha. */
  GPU_BLEND_INVERT,
  /** Order independent transparency.
   * NOTE: Cannot be used as is. Needs special setup (framebuffer, shader ...). */
  GPU_BLEND_OIT,
  /** Special blend to add color under and multiply dst color by src alpha. */
  GPU_BLEND_BACKGROUND,
  /** Custom blend parameters using dual source blending : SRC0 + SRC1 * DST
   * NOTE: Can only be used with _ONE_ Draw Buffer and shader needs to be specialized. */
  GPU_BLEND_CUSTOM,
} eGPUBlend;

typedef enum eGPUDepthTest {
  GPU_DEPTH_NONE = 0,
  GPU_DEPTH_ALWAYS, /* Used to draw to the depth buffer without really testing. */
  GPU_DEPTH_LESS,
  GPU_DEPTH_LESS_EQUAL, /* Default. */
  GPU_DEPTH_EQUAL,
  GPU_DEPTH_GREATER,
  GPU_DEPTH_GREATER_EQUAL,
} eGPUDepthTest;

typedef enum eGPUStencilTest {
  GPU_STENCIL_NONE = 0,
  GPU_STENCIL_ALWAYS,
  GPU_STENCIL_EQUAL,
  GPU_STENCIL_NEQUAL,
} eGPUStencilTest;

typedef enum eGPUStencilOp {
  GPU_STENCIL_OP_NONE = 0,
  GPU_STENCIL_OP_REPLACE,
  /** Special values for stencil shadows. */
  GPU_STENCIL_OP_COUNT_DEPTH_PASS,
  GPU_STENCIL_OP_COUNT_DEPTH_FAIL,
} eGPUStencilOp;

typedef enum eGPUFaceCullTest {
  GPU_CULL_NONE = 0, /* Culling disabled. */
  GPU_CULL_FRONT,
  GPU_CULL_BACK,
} eGPUFaceCullTest;

typedef enum eGPUProvokingVertex {
  GPU_VERTEX_LAST = 0,  /* Default. */
  GPU_VERTEX_FIRST = 1, /* Follow Blender loop order. */
} eGPUProvokingVertex;

#ifdef __cplusplus
extern "C" {
#endif

void GPU_blend(eGPUBlend blend);
void GPU_face_culling(eGPUFaceCullTest culling);
void GPU_depth_test(eGPUDepthTest test);
void GPU_provoking_vertex(eGPUProvokingVertex vert);
void GPU_front_facing(bool invert);
void GPU_depth_range(float near, float far);
void GPU_scissor_test(bool enable);
void GPU_line_smooth(bool enable);
void GPU_line_width(float width);
void GPU_logic_op_xor_set(bool enable);
void GPU_point_size(float size);
void GPU_polygon_smooth(bool enable);
void GPU_program_point_size(bool enable);
void GPU_scissor(int x, int y, int width, int height);
void GPU_scissor_get(int coords[4]);
void GPU_viewport(int x, int y, int width, int height);
void GPU_viewport_size_get_f(float coords[4]);
void GPU_viewport_size_get_i(int coords[4]);
void GPU_write_mask(eGPUWriteMask mask);
void GPU_color_mask(bool r, bool g, bool b, bool a);
void GPU_depth_mask(bool depth);
bool GPU_depth_mask_get(void);
void GPU_unpack_row_length_set(uint len);
void GPU_shadow_offset(bool enable);
void GPU_clip_distances(int enabled_len);
bool GPU_mipmap_enabled(void);
void GPU_state_set(eGPUWriteMask write_mask,
                   eGPUBlend blend,
                   eGPUFaceCullTest culling_test,
                   eGPUDepthTest depth_test,
                   eGPUStencilTest stencil_test,
                   eGPUStencilOp stencil_op,
                   eGPUProvokingVertex provoking_vert);

void GPU_stencil_reference_set(uint reference);
void GPU_stencil_write_mask_set(uint write_mask);
void GPU_stencil_compare_mask_set(uint compare_mask);

eGPUBlend GPU_blend_get(void);
eGPUDepthTest GPU_depth_test_get(void);
eGPUWriteMask GPU_write_mask_get(void);

void GPU_flush(void);
void GPU_finish(void);

#ifdef __cplusplus
}
#endif
