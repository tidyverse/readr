library("devtools")

# Don't forget to email javier@rstudio.com and ask him to check the IDE

revdep_check()
revdep_check_save_summary()
revdep_check_print_problems()

revdep_email(date = "July 29", draft = FALSE)
