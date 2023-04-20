import os

f = open(os.path.dirname(__file__) + "/main/include/cmbt_webserver_page.h", "w")
f.write(
    '#ifndef CMBT_WEBSERVER_PAGE_H\n#define CMBT_WEBSERVER_PAGE_H\n\nconst char index_html[] = R"rawliteral(\n'
)
f.write(open(os.path.dirname(__file__) + "/html_src/cmbt_webserver_page.html").read())
f.write('\n)rawliteral";\n\n#endif')
f.close()
