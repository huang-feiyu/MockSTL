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
 *
 * @param dst pointer to the memory location to <b>copy to</b>
 * @param src pointer to the memory location to <b>copy from</b>
 * @param count number of bytes to copy
 * @return <b>NULL</b> if behavior is undefined;<br/>
 *         <b>dst</b> otherwise
 */
void *imemcpy(void *dst, const void *src, size_t count) {
  if (dst == nullptr || src == nullptr) {
    return nullptr;
  }

  auto p_dst = static_cast<unsigned char *>(dst);
  auto p_src = static_cast<const unsigned char *>(src);
  if ((p_dst >= p_src && p_src + count > p_dst) || (p_src >= p_dst && p_dst + count > p_src)) {
    return nullptr;
  }

  for (size_t i = 0; i < count; i++) {
    p_dst[i] = p_src[i];
  }
  return dst;
}
