#!/bin/bash



# gdbus call -e -d com.system.configurationManager \
#   -o /com/system/configurationManager/Application/timeout_conf \
#   -m com.system.configurationManager.Application.Configuration.ChangeConfiguration \
#   "TimeoutPhrase" "<'New message text'>"

gdbus call -e -d com.system.configurationManager \
  -o /com/system/configurationManager/Application/timeout_conf \
  -m com.system.configurationManager.Application.Configuration.ChangeConfiguration \
  "Timeout" "<4>"


gdbus call -e -d com.system.configurationManager \
  -o /com/system/configurationManager/Application/timeout_conf \
  -m com.system.configurationManager.Application.Configuration.GetConfiguration