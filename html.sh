#!/bin/bash
#
function minimiza { 
export TELEPI=$(html-minifier --collapse-boolean-attributes --collapse-whitespace --decode-entities --html5 --minify-css --minify-js --process-conditional-comments --remove-attribute-quotes --remove-comments --remove-empty-attributes --remove-optional-tags --remove-redundant-attributes --remove-script-type-attributes  --remove-style-link-type-attributes --remove-tag-whitespace  --sort-attributes --sort-class-name --trim-custom-fragments --use-short-doctype $1)
}

echo "#ifndef TELEPIHTML_H"
echo "#define TELEPIHTML_H"
minimiza VictorLozada.css
echo 'const char VictorLozada[] PROGMEM = R"=====('$TELEPI')=====";'
minimiza index.html
echo 'const char indexhtml[] PROGMEM = R"=====('$TELEPI')=====";'
minimiza wifisetup.html
echo 'const char wifisetuphtml[] PROGMEM = R"=====('$TELEPI')=====";'
minimiza workmode.html
echo 'const char workmodehtml[] PROGMEM = R"=====('$TELEPI')=====";'
minimiza mqtt.html
echo 'const char mqtthtml[] PROGMEM = R"=====('$TELEPI')=====";'

echo "#endif //TELEPIHTML_H"
exit 0
