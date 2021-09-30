#!/bin/bash

sql_scripts_dir="GRR20176143"

for entry in "$sql_scripts_dir"/*
do  
    echo "======================"
    echo "$(basename $entry)"
    sqlite3 tpch.db < $entry
    echo "======================"
done
