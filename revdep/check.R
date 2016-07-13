library("devtools")

# Don't forget to email javier@rstudio.com and ask him to check the IDE

res <- revdep_check()
revdep_check_save_summary(res)
