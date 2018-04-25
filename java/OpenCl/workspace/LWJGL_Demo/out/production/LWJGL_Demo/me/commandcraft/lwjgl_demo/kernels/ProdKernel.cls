kernel void ProdKernel(global const float* a, global const float* b, global float* result, int const size) {
   const int itemId = get_global_id(0);
   if(itemId < size) {
      result[0] += a[itemId] * b[itemId];
   }
}