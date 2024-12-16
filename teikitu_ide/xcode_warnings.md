TAGS="TODO:|FIXME:|WARNING:"
ERRORTAG="ERROR:"

OUTPUT=$(find "${SRCROOT}" -name "*.h" -or -name "*.m" -or -name "*.swift" \( -not -path "${SRCROOT}/Carthage/*" \) -print0 | xargs -0 egrep --with-filename --line-number --only-matching "($TAGS).*\$|($ERRORTAG).*\$" | perl -p -e "s/($TAGS)/ warning: \$1/" | perl -p -e "s/($ERRORTAG)/ error: \$1/")

ECHO "$OUTPUT"

if [[ $OUTPUT == *" error: "* ]]
    then
    exit 1
fi

