type data = Js.t({. name: string });

let read = () => {"name": "ReasonML"};

let database: ref(option(data)) = ref(None);

let rec fetch = () => {
  switch (database^) {
    | Some(data) => data;
    | None => {
      database := Some(read());
      fetch();
    }
  }
};