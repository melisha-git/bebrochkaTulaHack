import axios from "axios";
import { useQuery } from "@tanstack/react-query";

export const getByName = (name) => {
  return useQuery(["data", name], async () => {
    const { data } = await axios.get(
      `http://192.168.0.105:8080/calendar/${name}`
    );
    return data;
  });
};
