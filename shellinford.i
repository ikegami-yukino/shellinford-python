%module shellinford

%include "std_map.i"
%include "std_string.i"
%include "stdint.i"
%template(MapIntInt) std::map<unsigned long long, unsigned long long>;

%{
  #include "shellinford/src/shellinford_fm_index.h"
  #include "shellinford/src/shellinford_bit_vector.h"
  #include "shellinford/src/shellinford_succinct_vector.h"
  #include "shellinford/src/shellinford_wavelet_matrix.h"
  #include "shellinford/src/shellinford_wavelet_tree.h"
%}

%include "shellinford/src/shellinford_fm_index.h"
%include "shellinford/src/shellinford_bit_vector.h"
%include "shellinford/src/shellinford_succinct_vector.h"
%include "shellinford/src/shellinford_wavelet_matrix.h"
%include "shellinford/src/shellinford_wavelet_tree.h"
