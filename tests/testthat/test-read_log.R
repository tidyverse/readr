test_that("read_log trims whitespace", {
  tf <- tempfile()
  on.exit(unlink(tf))

  writeLines('Nov  4 00:00:55 vrpweb1 httpd: 131.161.8.219 - - [04/Nov/2017:00:00:55 -0400] "GET /wp-includes/js/jquery/jquery-migrate.min.js?ver=1.4.1 HTTP/1.1" 200 10056 "http://www.colby.edu/" "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.72 Safari/537.36"
Nov 14 00:00:55 vrpweb1 httpd: 131.161.8.216 - - [04/Nov/2017:00:00:55 -0400] "GET /wp-content/plugins/wooslider-AxZp6o/assets/js/jquery.flexslider.min.js?ver=2.4.1-20170608 HTTP/1.1" 200 22414 "http://www.colby.edu/" "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/28.0.1500.72 Safari/537.36"',
  tf)

  res <- read_log(tf)

  expect_equal(res[[2]], c(4, 14))
})
