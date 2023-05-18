import axios from 'axios'
import { useQuery } from '@tanstack/react-query'

export const getAllPlace = () => {
	return useQuery(['alldata'], async () => {
		const { data } = await axios.get('http://192.168.0.105:8080/places')
		return data
	})
}

export const getById = id => {
	return useQuery(['data', id], async () => {
		const { data } = await axios.get(`http://192.168.0.105:8080/places/${id}`)
		return data
	})
}

export const getByCategory = category => {
	return useQuery(['category', category], async () => {
		const { data } = await axios.get(
			`http://192.168.0.105:8080/places/${category}`
		)
		return data
	})
}
