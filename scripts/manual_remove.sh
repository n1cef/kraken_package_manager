#!/bin/bash

manual_remove() {
    pkgname="$1"
    pkgver="$2"

    if [ -z "$pkgname" ] || [ -z "$pkgver" ]; then
        echo "ERROR: Missing arguments for manual_remove."
        exit 1
    fi

    local package_path="/var/lib/kraken/packages/$pkgname-$pkgver"
    local files_list="$package_path/FILES"

    # Check if FILES exists
    if [ ! -f "$files_list" ]; then
        echo "ERROR: FILES list not found for package $pkgname-$pkgver."
        exit 1
    fi

    echo "Manual removal in progress for $pkgname-$pkgver..."

    # Read each line (file path) from FILES and remove it
    while IFS= read -r file; do
        if [ -f "$file" ]; then
            echo "Removing file: $file"
            sudo rm -f "$file"
        elif [ -d "$file" ]; then
            echo "Skipping directory: $file"
        else
            echo "WARNING: File $file does not exist."
        fi
    done < "$files_list"

    # Remove package metadata directory after files are deleted
    echo "Cleaning up package metadata..."
    sudo rm -rf "$package_path"

    echo "Package $pkgname-$pkgver removed successfully."
}
