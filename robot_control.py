from dash import Dash, html, dcc, Input, Output,ctx
from dash import Dash, dcc, html, dash_table, Input, Output, callback
import dash_bootstrap_components as dbc
from dash_bootstrap_templates import ThemeChangerAIO, template_from_url
import dash_daq as daq
import serial
import time
prev=0
dbc_css = "https://bootswatch.com/5/vapor/bootstrap.min.css"

app = Dash("F",external_stylesheets=[dbc.themes.BOOTSTRAP,dbc_css])


server=app.server
ser=serial.Serial('COM6',9600,timeout=1)
ser.flush()

app.layout = dbc.Container([
    dbc.Button('Move Forward', id='btn-1', n_clicks=0),
    html.Br(),
    html.Br(),

    dbc.Button('Move Backward', id='btn-2', n_clicks=0),
    html.Br(),
    html.Br(),

    dbc.Button('Move Left', id='btn-3', n_clicks=0),
    html.Br(),
    html.Br(),

    dbc.Button('Move Right', id='btn-4', n_clicks=0),
    html.Br(),
    html.Br(),
    dbc.Button('Brake', id='btn-5', n_clicks=0),
    html.Br(),
    html.Br(),
    html.Pre(id='output-1'),
    html.Pre(id='output-2'),
    html.Pre(id='output-3'),
    html.Pre(id='output-4'),
    html.Pre(id='output-5'),
])

@app.callback(
    Output('output-1','value'),
    Input("btn-1", "n_clicks"),
)
def move_forward(btn1):
    print(btn1)
    if "btn-1"==ctx.triggered_id:
        print(f"Button-1 Clicked: {ctx.triggered_id}")
       
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b'w'))


    return "Robot moved forward"
@app.callback(
    Output('output-2','value'),
    Input("btn-2", "n_clicks"),
)
def move_forward(btn2):
    print(btn2)
    if "btn-2"==ctx.triggered_id:
        print(f"Button-1 Clicked: {ctx.triggered_id}")
       
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b's'))


    return "Robot moved backward"
@app.callback(
    Output('output-3','value'),
    Input("btn-3", "n_clicks"),
)
def move_left(btn3):
    print(btn3)
    if "btn-3"==ctx.triggered_id:
        print(f"Button-1 Clicked: {ctx.triggered_id}")
       
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b'a'))


    return "Robot moved left"
@app.callback(
    Output('output-4','value'),
    Input("btn-4", "n_clicks"),
)
def move_forward(btn4):
    print(btn4)
    if "btn-4"==ctx.triggered_id:
        print(f"Button-1 Clicked: {ctx.triggered_id}")
       
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b'd'))


    return "Robot moved right"

@app.callback(
    Output('output-5','value'),
    Input("btn-5", "n_clicks"),
)
def move_forward(btn5):
    print(btn5)
    if "btn-5"==ctx.triggered_id:
        print(f"Button-1 Clicked: {ctx.triggered_id}")
       
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b'e'))


    return "Robot brake"

if __name__ == '__main__':
    app.run_server(debug=False)