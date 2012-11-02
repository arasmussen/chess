#!/bin/sh
cd "$(git rev-parse --show-toplevel)"
rm -f web/db.sql
mysqldump -u root -p$DB_ROOT_PASSWORD chess > web/db.sql
chmod 755 web/db.sql
git add web/db.sql
exit 0
