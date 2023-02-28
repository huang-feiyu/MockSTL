#pragma once

#include <cstddef>

/**
 * Copies count bytes from the object pointed to by src to the object pointed to by dst.
 * Both objects are reinterpreted as arrays of unsigned char.
 *
 * @details
 * <ul>
 * <li>If the objects overlap, the behavior is undefined.</li>
 * <li>If either dst or src is an invalid or null pointer, the behavior is undefined, even if count is zero.</li>
 * <li>If the objects are potentially-overlapping or not TriviallyCopyable, the behavior of memcpy is not
 * specified and may be undefined.</li>
 * </ul>
 * But in normal interview, memcpy is treated as memmove. That is: memory overlapping is permitted.
 *
 * @param dst pointer to the memory location to <b>copy to</b>
 * @param src pointer to the memory location to <b>copy from</b>
 * @param count number of bytes to copy
 * @return <b>NULL</b> if behavior is undefined;<br/>
 *         <b>dst</b> otherwise
 */
void *imemcpy(void *dst, const void *src, size_t count) {
  if ((src == nullptr) || (dst == nullptr)) {
    return nullptr;
  }
  // NOTE: implementation from mit-pdos/xv6
  auto p_dst = static_cast<unsigned char *>(dst);
  auto p_src = static_cast<const unsigned char *>(src);

  if ((p_src < p_dst) && (p_src + count > p_dst)) {
    // src: 0x1, 0x2, 0x3
    // dst:      0x2, 0x3, 0x4
    p_src += count;  // => src: 0x4
    p_dst += count;  // => dst: 0x5
    // count[3]: 0x4 -> 0x3
    // count[2]: 0x3 -> 0x2
    // count[1]: 0x2 -> 0x1
    while (count-- > 0) {
      *--p_dst = *--p_src;
    }
  } else {
    // src:      0x2, 0x3, 0x4
    // dst: 0x1, 0x2, 0x3
    while (count-- > 0) {
      *p_dst++ = *p_src++;
    }
  }
  return dst;
}
