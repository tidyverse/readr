# APCalign

<details>

* Version: 0.1.3
* GitHub: https://github.com/traitecoevo/APCalign
* Source code: https://github.com/cran/APCalign
* Date/Publication: 2023-11-16 22:43:53 UTC
* Number of recursive dependencies: 97

Run `revdepcheck::cloud_details(, "APCalign")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Complete output:
      > # This file is part of the standard setup for testthat.
      > # It is recommended that you do not modify it.
      > #
      > # Where should you do additional test configuration?
      > # Learn more about the roles of various files in:
      > # * https://r-pkgs.org/tests.html
      > # * https://testthat.r-lib.org/reference/test_package.html#special-files
    ...
        6. │     └─dplyr:::check_nth_default(default, x = x)
        7. │       └─vctrs::vec_init(x)
        8. └─vctrs:::stop_scalar_type(`<fn>`(NULL), "x", `<fn>`(vec_init()))
        9.   └─vctrs:::stop_vctrs(...)
       10.     └─rlang::abort(message, class = c(class, "vctrs_error"), ..., call = call)
      
      [ FAIL 1 | WARN 0 | SKIP 0 | PASS 85 ]
      Error: Test failures
      In addition: There were 18 warnings (use warnings() to see them)
      Execution halted
    ```

## In both

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 4 marked UTF-8 strings
    ```

