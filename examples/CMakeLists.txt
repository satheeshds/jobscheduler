add_subdirectory(cli_client)

add_custom_target(tidy_examples
    DEPENDS tidy_cli_client
    COMMENT "Tidying examples"
)
