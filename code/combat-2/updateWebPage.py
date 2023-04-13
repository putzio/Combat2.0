import os

f = open(os.path.dirname(__file__) + "/html_src/web_server_page.h", "w")
f.write(
    '#ifndef WEB_SERVER_PAGE_H\n#define WEB_SERVER_PAGE_H\n\nconst char index_html[] = R"rawliteral(\n'
)
f.write(open(os.path.dirname(__file__) + "/html_src/web_server_page.html").read())
f.write('\n)rawliteral";\n\n#endif')
f.close()
