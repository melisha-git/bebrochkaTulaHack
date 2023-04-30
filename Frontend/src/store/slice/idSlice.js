import { createSlice } from '@reduxjs/toolkit'

const initialState = {
	value: 0,
	place: {},
	category: 'bar'
}

export const idSlice = createSlice({
	name: 'id',
	initialState,
	reducers: {
		setId: (state, action) => {
			state.value = action.payload
		},
		setPlace: (state, action) => {
			state.place = action.payload
		},
		setCategory: (state, action) => {
			state.category = action.payload
		}
	}
})

export const { setId, setPlace, setCategory } = idSlice.actions

export default idSlice.reducer
