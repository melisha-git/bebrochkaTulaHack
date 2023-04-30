import axios from "axios";
import { useMutation } from "@tanstack/react-query";

export const userPost = () => {
  useMutation({
    mutationFn: (newTodo) => {
      return axios.post("/todos", newTodo);
    },
  });
};
