#!/bin/bash



gdbus call -e -d com.system.configurationManager \
  -o /com/system/configurationManager/Application/timeout1_conf \
  -m com.system.configurationManager.Application.Configuration.ChangeConfiguration \
  "TimeoutPhrase" "<'father'>"

# gdbus call -e -d com.system.configurationManager \
#   -o /com/system/configurationManager/Application/timeout_conf \
#   -m com.system.configurationManager.Application.Configuration.ChangeConfiguration \
#   "Timeout" "<1>"


# gdbus call -e -d com.system.configurationManager \
#   -o /com/system/configurationManager/Application/timeout_conf \
#   -m com.system.configurationManager.Application.Configuration.GetConfiguration


# gdbus introspect --session --dest com.system.configurationManager -o /com/system/configurationManager/Application/timeout_conf