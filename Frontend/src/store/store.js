import { configureStore } from "@reduxjs/toolkit";
import counterReducer from "./slice/countSlice";
import geoReducer from "./slice/geoSlice";
import idReducer from "./slice/idSlice";

export const store = configureStore({
  reducer: { counterReducer, geoReducer, idReducer },
});
