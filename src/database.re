open DataModel;

let read = () => {
  todos: [|
    {name: "One"}
  |]
};

let database: ref(option(DataModel.root)) = ref(None);

let rec fetch = () => {
  switch (database^) {
    | Some(data) => data;
    | None => {
      database := Some(read());
      fetch();
    }
  }
};