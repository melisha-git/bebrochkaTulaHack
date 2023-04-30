import { useEffect } from 'react'
import { useSelector, useDispatch } from 'react-redux'

import { getById } from '@/service/place.service.js'
import PlacePage from '@/components/Place/PlacePage/PlacePage'
import { setPosition } from '@/store/slice/geoSlice'

export default function PlacePageApi() {
	const position = useSelector(state => state.geoReducer.position)
	const id = useSelector(state => state.idReducer.value)
	const dispatch = useDispatch()
	const { data, isSuccess } = getById(+id)
	useEffect(() => {
		if (isSuccess) {
			dispatch(setPosition([+data[0].coordinates[0], +data[0].coordinates[1]]))
		}
	}, [data])
	return <>{isSuccess && <PlacePage data={data[0]} />}</>
}
