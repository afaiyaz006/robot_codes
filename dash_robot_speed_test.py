from dash import Dash, html, dcc, Input, Output,ctx
from dash import Dash, dcc, html, dash_table, Input, Output, callback
import dash_bootstrap_components as dbc
from dash_bootstrap_templates import ThemeChangerAIO, template_from_url
import dash_daq as daq
import serial
import time

dbc_css = "https://bootswatch.com/5/vapor/bootstrap.min.css"

app = Dash("F",external_stylesheets=[dbc.themes.BOOTSTRAP,dbc_css])


server=app.server
ser=serial.Serial('COM6',9600,timeout=1)
ser.flush()

app.layout = dbc.Container([
    dbc.Button('Test Motor 1', id='btn-nclicks-1', n_clicks=0),
    html.Br(),
    html.Br(),

    dbc.Button('Test Motor 2', id='btn-nclicks-2', n_clicks=0),
    html.Pre(id='output-1'),
    html.Pre(id='output-2'),

    
    daq.Gauge(
     
        id='Motor',
        label="motor",
        units='PWM',
        value=0,
        max=255,
        min=0
    ),
    dcc.Interval(
            id='interval-component-1',
            interval=100, # in milliseconds
            n_intervals=0
    ),
    
   
])
@app.callback(
    Output('Motor','value'),
    Input('interval-component-1', 'n_intervals')
)
def update_motor(n):
   
    if not ser.is_open:
        ser.open()
        
    data=ser.read(1)
    speed=0    
        
    if(len(data)>0):
            speed=ord(data)
    print(speed)
    return speed    
    

@app.callback(
    Output('output-1', 'children'),
    Input("btn-nclicks-1", "n_clicks"),
)
def test_motor_1(btn1):
    print(btn1)
    if "btn-nclicks-1"==ctx.triggered_id:
        print(f"Button-1 Clicked: {ctx.triggered_id}")
       
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b'x'))


    return "Motor-1 tested at"+str(time.time())

@app.callback(
    Output('output-2', 'children'),
    Input("btn-nclicks-2", "n_clicks"),
)

def test_motor_2(btn2):
    print(btn2)
    if "btn-nclicks-2"==ctx.triggered_id:
        print(f"Button-2 Clicked: {ctx.triggered_id}")
        if not ser.is_open:
            ser.open()
        ser.write(bytes(b'y'))
    return  "Motor-2 test at"+str(time.time())

if __name__ == '__main__':
    app.run_server(debug=False)