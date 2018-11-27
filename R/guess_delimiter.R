# Ideally we'd like to eliminate this function altogether and port
# it into a package that can be called once this function
# is cleaned and refactored
guess_delim <- function(file, n_max = 1000, threshold_rows = 0.9,
                        delim = c(',', '\t', ';', ' ', ':')) {

  # This should also consider passing the locale
  data <-
    tryCatch(
      readr::read_lines(file, n_max = n_max),
      error = function(e) NA_character_
    )

  # Split each line of the csv file into a list
  data <- strsplit(data, "\n")

  # Exclude empty rows
  filtered_data <- data[!vapply(data, function(x) is.null(x) | length(x) == 0, logical(1))]

  # Split each letter of the row and THEN turn into factor so that the results to table counts all
  # non appearing delimiters as zero.
  delimiter_counts <- lapply(filtered_data, function(row) table(factor(strsplit(row, "")[[1]], levels = delim)))

  # First check: is there one and only delimiter repeated the same number
  # of times in all rows? If so, exit and return that delimiter
  perfect_match <- detect_one_match(delimiter_counts)

  # If perfect match is not TRUE it returns NA
  if (!is.na(perfect_match)) return(perfect_match)

  # Get the number of rows read after deleting the empty rows
  # in filtered_data because otherwise the threshold is calculated
  # wrongly
  rows_read <- min(length(filtered_data), guess_max)

  # Loop through each line if the csv file, separate each column and get
  # the frequency of each character
  res <- lapply(filtered_data, function(row) table(strsplit(row, "")[[1]]))

  table_names <- lapply(res, names)

  all_chars <- unlist(table_names)

  all_chars <- all_chars[all_chars %in% delim]

  # What is the percentage of rows where the
  # delimiter is repeated?
  prop_repetition <- table(all_chars) / rows_read

  # If one or more delimiters are repeated in all rows
  if (one_true(prop_repetition == 1) %in% c('one true', '> one true')) {
    # Then get their names
    repeated_names <- names(which(prop_repetition == 1))
  } else if (any(prop_repetition > threshold_rows)) {
    # Otherwise get the delimiters which were repeated
    # more times than the threshold
    repeated_names <- names(which(prop_repetition > threshold_rows))
  } else {
    # Because no delimiter was matched at or over the threshold of rows
    return (NA_character_)
  }

  unique_repetitions <- lapply(repeated_names, function(delimiter) {
    unique_vals <- unique(unlist(lapply(res, `[`, delimiter)))
    unique_vals[!is.na(unique_vals)]
  })

  unique_repetitions <- stats::setNames(unique_repetitions, repeated_names)

  if (length(unique_repetitions) == 0) return(NA_character_)

  same_count_delimiter <-
    sapply(unique_repetitions, function(x) length(unique(x)) == 1)

  matched_delimiters <- one_true(same_count_delimiter)

  if (matched_delimiters == "one true") {

    unique_delimiter <- names(same_count_delimiter[which(same_count_delimiter)])

    return(unique_delimiter)

  } else if (matched_delimiters == '> one true') {
    # If there were two delimiters that have a single number
    # repeated in all rows and are at 90% of the rows or more
    # filter whether these two are in the prefered delimiters and
    # pick in the order of preference in the preferred delimiters

    conflicting_delims <- names(same_count_delimiter)[which(same_count_delimiter)]
    chosen_delimiter <- pick_preference(conflicting_delims, delim)

    return(chosen_delimiter)
  } else {
    undecided_delims <- names(same_count_delimiter)
    chosen_delimiter <- pick_preference(undecided_delims, delim)

    if (!is.na(chosen_delimiter)) return(chosen_delimiter)
  }

  NA_character_ # no format was found
}

detect_one_match <- function(x) {
  # x here is a list where each slot is a count of the occurrences of each of the delimiters
  merged_counts <- as.data.frame(do.call(rbind, x))

  columns_only_zeros <- vapply(merged_counts, function(x) all(x == 0), logical(1))

  # Exclude all columns that only contain zero and check for columns with only one number
  repeated_columns <- vapply(merged_counts[!columns_only_zeros], function(x) all(x[1] == x), logical(1))

  index_delim <- which(repeated_columns)

  # Only if a delimiter is repeated the same times in all rows it is
  # returned. Otherwise the function returns an NA
  if (length(index_delim) == 1) return(names(repeated_columns)[index_delim])

  NA_character_
}

one_true <- function(x) {
  table_trues <- table(x)

  # If there's only ONE true, return 'one true',
  # if more than one true, return '> one true'
  # else 'no true'
  if (any(as.logical(names(table_trues)))) {
    if (table_trues['TRUE'] == 1) {
      return("one true")
    } else {
      return("> one true")
    }
  }

  "no true"
}


# Matches the `match` in `pool_matches` and brings
# according to the order in `pool_matches`
pick_preference <- function(match, pool_matches) {
  available_delims <- match %in% pool_matches

  if (any(available_delims)) {
    # We turn to factor in order to sort according to the allowed formats.
    # This way when we subset we keep the order of preference of files.
    sorted_formats <- sort(factor(pool_matches, levels = pool_matches))
    chosen_delimiter <- sorted_formats[which(sorted_formats %in% match)[1]]
    chosen_delimiter <- as.character(chosen_delimiter)
    return(chosen_delimiter)
  }

  NA_character_
}
