let component = ReasonReact.statelessComponent("ReactApp");

let make = (~name, _children) => {
  ...component,
  render: (self) => <p> {ReasonReact.stringToElement("Hello " ++ name ++ "!")} </p>
};