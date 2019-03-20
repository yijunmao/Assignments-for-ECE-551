unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (y < 0) {
    return 0;
  }
  else {
    return x * power(x, y - 1);
  }
}
