/* The Express module is the community-maintained binding to ExpressJS
   open`-ing it exposes its functions to the current module! */ 
open Express;

/* We can create a new app pretty easily, just like the JS version! */
let app = express();

/* Reason has template strings between quotes that look like "{j|" and "|j}" */
let renderPage = (innerHtml) => {j|
  <html>
    <head>
      <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css">
    </head>
    <body>
      <div id="root">$innerHtml</div>
      <script src="/bundle.js"></script>
    </body>
  </html>
|j};

App.get(app, ~path="/bundle.js") @@
Middleware.from(
  (_req, res, _next) => {
    Response.sendFile(res, "bundle.js", {"root": "/app"});
  }
);

/* Set up a listener on the "/" path to serve a string */
App.get(app, ~path="/") @@
Middleware.from(
  (_req, res, _next) => {
    /* Fetch data from our "database" */
    let data = Database.fetch();

    /* We can server render a React app here and send it to the client! */
    let reactHtml = ReactDOMServerRe.renderToString(<ReactApp name=(data##name) />);
    
    Response.sendString(res, renderPage(reactHtml));
  }
);

/* We're gonna send JSON on the "/status" path! */
App.get(app, ~path="/status") @@
Middleware.from(
  (_req, res, _next) => {
    let status = Js.Dict.empty();
    Js.Dict.set(status, "ok", Js.Json.boolean(Js.true_));
    
    Response.sendJson(res, Js.Json.object_(status));
  }
);

/* An `external` binds a raw JS value to Reason. Here we sat that we want the value
   in `process.env.PORT` by using `[@bs.val]` and assigning our `external` to the string
   we want. Then using a type annotation we say it's a string */
[@bs.val] external processEnvPort : string = "process.env.PORT";

/* `int_of_string` converts a string to an int */
let port = int_of_string(processEnvPort);

/* Listen for requests :D */
App.listen(app, ~port=port, ());