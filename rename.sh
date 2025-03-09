for dir in M*; do
  if [[ "$dir" =~ ^M([0-9]{2})([CL])([0-9])$ ]]; then
    module=$((10#${BASH_REMATCH[1]}))
    if [ "${BASH_REMATCH[2]}" = "C" ]; then
      type="Challenge"
    else
      type="Learning"
    fi
    new_name="Module0${module}_${type}"
    echo "$dir -> $new_name"
    mv "$dir" "$new_name"
  fi
done
