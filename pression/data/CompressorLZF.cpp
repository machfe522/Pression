
/* Copyright (c) 2012-2016, Stefan Eilemann <eile@eyescale.ch>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "CompressorLZF.h"

#include <lunchbox/buffer.h>
#include <pression/data/Registry.h>

extern "C" {
#include "liblzf/lzf.h"
}

namespace pression
{
namespace data
{
namespace
{
const bool _initialized =
    Registry::getInstance().registerEngine<CompressorLZF>({.69f, .25f});
}

void CompressorLZF::compressChunk(const uint8_t* const data, const size_t size,
                                  Result& output)
{
    if (!_initialized)
        return;
    output.setSize(lzf_compress(data, uint32_t(size), output.getData(),
                                output.getMaxSize()));
}

void CompressorLZF::decompressChunk(const uint8_t* input,
                                    const size_t inputSize, uint8_t* const data,
                                    const size_t size)
{
    if (!_initialized)
        return;

    lzf_decompress(input, uint32_t(inputSize), data, uint32_t(size));
}
}
}
