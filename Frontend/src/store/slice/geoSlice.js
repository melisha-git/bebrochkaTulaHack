import { createSlice } from "@reduxjs/toolkit";

const initialState = {
  position: [54.193122, 37.617348],
};

export const geoSlice = createSlice({
  name: "geoPosition",
  initialState,
  reducers: {
    setPosition: (state, actions) => {
      state.position = actions.payload;
    },
  },
});

export const { setPosition } = geoSlice.actions;

export default geoSlice.reducer;
