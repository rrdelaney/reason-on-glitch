type todo = {
  name: string
};

type root = {
  todos: array(todo)
};

module Encode {
  let todo = (data: todo) =>
    Json.Encode.(
      object_([
        ("name", string(data.name))
      ])
    );
    
  let root = (data: root) =>
    Json.Encode.(
      object_([
        ("todos", Array.map(todo, data.todos) |> jsonArray)
      ])
    );
};

module Decode {
  let todo = (json) =>
    Json.Decode.{
      name: json |> field("name", string)
    };
    
  let root = (json) =>
    Json.Decode.{
      todos: json |> field("todos", array(todo))
    };
};