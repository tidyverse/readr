## Current state

readr is in somewhat of a weird state currently. We have both the older v1 parsing code base, as well as calls to vroom under the hood in v2.

In addition there are still some parts, like the `parse_()` functions which just use the v1 code, as there are not currently analogous APIs in vroom.

## Known outstanding issues

Lazy reading causes problems for people in practice because of file locking on windows.
This makes the technique less effective then it would otherwise be unfortunately.

The v1 parser has some issues around skipping lines and quoting. There was a bunch of flux in how skipped lines were counted.

For known issues for the v2 parser see the vroom MAINTENANCE.md document.

## Future directions

I think eventually the v1 parsing code should be removed entirely and either
the vroom codebase should be included directly in readr and vroom should be archived, or
the two should both continue to exist with the readr functions being a lightweight
shim over the calls to vroom.
