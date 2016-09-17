#!/bin/bash
if [ "$1" = "native" ];then
perl -i -p -e 's/(?<=MONGO_HOST\s=\s")mongo/127.0.0.1/g' settings.py
perl -i -p -e 's/(?<=REDIS_HOST\s=\s")redis/127.0.0.1/g' settings.py
perl -i -p -e 's/(?<=@)rabbit/localhost/g' celery_tasks/celeryconfig.py
elif [ "$1" = "remote" ];then
perl -i -p -e 's/(?<=MONGO_HOST\s=\s")127\.0\.0\.1/mongo/g' settings.py
perl -i -p -e 's/(?<=REDIS_HOST\s=\s")127\.0\.0\.1/redis/g' settings.py
perl -i -p -e 's/(?<=@)localhost/rabbit/g' celery_tasks/celeryconfig.py
fi
