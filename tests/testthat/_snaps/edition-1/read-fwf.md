# error on empty spec (#511, #519)

    Code
      read_fwf(I(txt), pos)
    Condition
      Error:
      ! Zero-length begin and end specifications not supported

# error on negatives in fwf spec

    Code
      read_fwf(I(txt), pos)
    Condition
      Error:
      ! Begin offset (-2) must be greater than 0

