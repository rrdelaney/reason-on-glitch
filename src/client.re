[@bs.val] external initialState : Js.Json.t = "__init";

let data = DataModel.Decode.root(initialState);

ReactDOMRe.renderToElementWithId(<ReactApp data=data />, "root");