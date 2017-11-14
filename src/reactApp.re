open DataModel;

let component = ReasonReact.statelessComponent("ReactApp");

let make = (~data: root, _children) => {
  ...component,
  render: (_self) => <div>
    <ul>
      {Array.map(todo => {
        <li>{ReasonReact.stringToElement(todo.name)}</li>
      }, data.todos) |> ReasonReact.arrayToElement}
    </ul>
  </div>
};