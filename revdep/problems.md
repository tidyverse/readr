# rapbase

<details>

* Version: 1.23.0
* GitHub: https://github.com/Rapporteket/rapbase
* Source code: https://github.com/cran/rapbase
* Date/Publication: 2022-08-17 14:20:02 UTC
* Number of recursive dependencies: 110

Run `revdepcheck::cloud_details(, "rapbase")` for more info

</details>

## Newly broken

*   checking tests ... ERROR
    ```
      Running ‘testthat.R’
    Running the tests in ‘tests/testthat.R’ failed.
    Last 13 lines of output:
      ══ Failed tests ════════════════════════════════════════════════════════════════
      ── Failure ('test-github.R:6'): contributors are provided ──────────────────────
      class(getGithub("contributors", "rapbase")) not equal to "character".
      1/1 mismatches
      x[1]: "NULL"
      y[1]: "character"
      ── Failure ('test-github.R:10'): key can be provided ───────────────────────────
      grepl("ssh-rsa", getGithub("keys", "areedv")) is not TRUE
      
      `actual`:       
      `expected`: TRUE
      
      [ FAIL 2 | WARN 0 | SKIP 25 | PASS 190 ]
      Error: Test failures
      Execution halted
    ```

