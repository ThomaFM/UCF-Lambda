/**
 * Author: Brian Barak
 * Date: 2025-10-08
 * License: CC0
 * Source: folklore
 * Description: Measure time elapsed
 * Status: tested
 */
#pragma once

using namespace std::chrono;
auto t1 = steady_clock::now();
duration_cast<microseconds>(t2 - t1).count()/1e6
